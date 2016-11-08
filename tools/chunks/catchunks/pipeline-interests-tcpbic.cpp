/**
 * Copyright (c) 2016,  Regents of the University of California,
 *                      Colorado State University,
 *                      University Pierre & Marie Curie, Sorbonne University.
 *
 * This file is part of ndn-tools (Named Data Networking Essential Tools).
 * See AUTHORS.md for complete list of ndn-tools authors and contributors.
 *
 * ndn-tools is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * ndn-tools is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * ndn-tools, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 *
 * See AUTHORS.md for complete list of ndn-cxx authors and contributors.
 *
 * @author Shuo Yang
 * @author Weiwei Liu
 */

#include "pipeline-interests-tcpbic.hpp"

#include <cmath>

namespace ndn {
namespace chunks {
namespace tcpbic {

PipelineInterestsTcpBic::PipelineInterestsTcpBic(Face& face, RttEstimator& rttEstimator,
		RateEstimator& rateEstimator, const Options& options)
		: PipelineInterests(face), m_options(options), m_rttEstimator(rttEstimator), m_rateEstimator(
				rateEstimator), m_scheduler(m_face.getIoService()), m_nextSegmentNo(0), m_receivedSize(0), m_highData(
				0), m_highInterest(0), m_recPoint(0), m_nInFlight(0), m_nReceived(0), m_nLossEvents(0), m_nRetransmitted(
				0), m_cwnd(m_options.initCwnd), m_ssthresh(m_options.initSsthresh), m_hasFailure(false), m_failedSegNo(
				0), m_nPackets(0), m_nBits(0), is_bic_ss(false), bic_target_win(0), bic_min_win(0), bic_max_win(MAX_INT),
        bic_ss_cwnd(0), bic_ss_target(0)
{
	if (m_options.isVerbose) {
		std::cerr << m_options;
	}
}

PipelineInterestsTcpBic::~PipelineInterestsTcpBic()
{
	cancel();
}

void PipelineInterestsTcpBic::doRun()
{
	// record the start time of running pipeline
	m_startTime = time::steady_clock::now();

	// count the excluded segment
	m_nReceived++;

	// schedule the event to check retransmission timer
	m_scheduler.scheduleEvent(m_options.rtoCheckInterval, [this] {checkRto();});

	// schedule the event to check rate at rate interval timer
	m_scheduler.scheduleEvent(time::milliseconds((int)(m_options.rateInterval*1000)), [this] {checkRate();});

	sendInterest(getNextSegmentNo(), false);
}

void PipelineInterestsTcpBic::doCancel()
{
	for (const auto& entry : m_segmentInfo) {
		const SegmentInfo& segInfo = entry.second;
		m_face.removePendingInterest(segInfo.interestId);
	}
	m_segmentInfo.clear();
	m_scheduler.cancelAllEvents();
}

void PipelineInterestsTcpBic::checkRate()
{
	if (isStopping())
		return;

	time::steady_clock::duration cur = time::steady_clock::now() - m_startTime;
	double now = (double) cur.count() / 1000000000;

	m_rateEstimator.addMeasurement(now, m_nPackets, m_nBits);

	m_nPackets = 0;
	m_nBits = 0;
	m_scheduler.scheduleEvent(time::milliseconds((int)(m_options.rateInterval*1000)), [this] {checkRate();});

}

void PipelineInterestsTcpBic::checkRto()
{
	if (isStopping())
		return;

	int timeoutCount = 0;

	for (auto& entry : m_segmentInfo) {
		SegmentInfo& segInfo = entry.second;
		if (segInfo.state != SegmentState::InRetxQueue && // do not check segments currently in the retx queue
				segInfo.state != SegmentState::RetxReceived) { // or already-received retransmitted segments
			Milliseconds timeElapsed = time::steady_clock::now() - segInfo.timeSent;
			if (timeElapsed.count() > segInfo.rto.count()) { // timer expired?
				uint64_t timedoutSeg = entry.first;
				m_retxQueue.push(timedoutSeg); // put on retx queue
				segInfo.state = SegmentState::InRetxQueue; // update status
				timeoutCount++;
			}
		}
	}

	if (timeoutCount > 0) {
		handleTimeout(timeoutCount);
	}

	// schedule the next check after predefined interval
	m_scheduler.scheduleEvent(m_options.rtoCheckInterval, [this] {checkRto();});
}

void PipelineInterestsTcpBic::sendInterest(uint64_t segNo, bool isRetransmission)
{
	if (isStopping())
		return;

	if (m_hasFinalBlockId && segNo > m_lastSegmentNo && !isRetransmission)
		return;

	if (!isRetransmission && m_hasFailure)
		return;

	if (m_options.isVerbose) {
		if (isRetransmission)
			std::cerr << "Retransmitting segment #" << segNo << std::endl;
		else
			std::cerr << "Requesting segment #" << segNo << std::endl;
	}

	if (isRetransmission) {
		auto ret = m_retxCount.insert(std::make_pair(segNo, 1));
		if (ret.second == false) { // not the first retransmission
			m_retxCount[segNo] += 1;
			if (m_retxCount[segNo] > m_options.maxRetriesOnTimeoutOrNack) {
				return handleFail(segNo,
						"Reached the maximum number of retries ("
								+ to_string(m_options.maxRetriesOnTimeoutOrNack) + ") while retrieving segment #"
								+ to_string(segNo));
			}

			if (m_options.isVerbose) {
				std::cerr << "# of retries for segment #" << segNo << " is " << m_retxCount[segNo]
						<< std::endl;
			}
		}

		m_face.removePendingInterest(m_segmentInfo[segNo].interestId);
	}

	Interest interest(Name(m_prefix).appendSegment(segNo));
	interest.setInterestLifetime(m_options.interestLifetime);
	interest.setMustBeFresh(m_options.mustBeFresh);
	interest.setMaxSuffixComponents(1);

	auto interestId = m_face.expressInterest(interest,
			bind(&PipelineInterestsTcpBic::handleData, this, _1, _2),
			bind(&PipelineInterestsTcpBic::handleNack, this, _1, _2),
			bind(&PipelineInterestsTcpBic::handleLifetimeExpiration, this, _1));

	m_nInFlight++;

	if (isRetransmission) {
		SegmentInfo& segInfo = m_segmentInfo[segNo];
		segInfo.state = SegmentState::Retransmitted;
		segInfo.rto = m_rttEstimator.getEstimatedRto();
		segInfo.timeSent = time::steady_clock::now();
		m_nRetransmitted++;
	}
	else {
		m_highInterest = segNo;
		Milliseconds rto = m_rttEstimator.getEstimatedRto();
		SegmentInfo segInfo { interestId, SegmentState::FirstTimeSent, rto, time::steady_clock::now() };

		m_segmentInfo.emplace(segNo, segInfo);
	}
}

void PipelineInterestsTcpBic::schedulePackets()
{
	int availableWindowSize = static_cast<int>(m_cwnd) - m_nInFlight;
	while (availableWindowSize > 0) {
		if (!m_retxQueue.empty()) { // do retransmission first
			uint64_t retxSegNo = m_retxQueue.front();
			m_retxQueue.pop();

			auto it = m_segmentInfo.find(retxSegNo);
			if (it == m_segmentInfo.end()) {
				continue;
			}
			// the segment is still in the map, it means that it needs to be retransmitted
			sendInterest(retxSegNo, true);
		}
		else { // send next segment
			sendInterest(getNextSegmentNo(), false);
		}
		availableWindowSize--;
	}
}

void PipelineInterestsTcpBic::handleData(const Interest& interest, const Data& data)
{
	if (isStopping())
		return;

	m_nPackets += 1;
	m_nBits += data.getContent().size() * 8;

	// Data name will not have extra components because MaxSuffixComponents is set to 1
	BOOST_ASSERT(data.getName().equals(interest.getName()));

	if (!m_hasFinalBlockId && !data.getFinalBlockId().empty()) {
		m_lastSegmentNo = data.getFinalBlockId().toSegment();
		m_hasFinalBlockId = true;
		cancelInFlightSegmentsGreaterThan(m_lastSegmentNo);
		if (m_hasFailure && m_lastSegmentNo >= m_failedSegNo) {
			// previously failed segment is part of the content
			return onFailure(m_failureReason);
		}
		else {
			m_hasFailure = false;
		}
	}

	uint64_t recvSegNo = data.getName()[-1].toSegment();
	if (m_highData < recvSegNo) {
		m_highData = recvSegNo;
	}

	SegmentInfo& segInfo = m_segmentInfo[recvSegNo];
	if (segInfo.state == SegmentState::RetxReceived) {
		m_segmentInfo.erase(recvSegNo);
		return; // ignore already-received segment
	}

	Milliseconds rtt = time::steady_clock::now() - segInfo.timeSent;

	if (m_options.isVerbose) {
		std::cerr << "Received segment #" << recvSegNo << ", rtt=" << rtt.count() << "ms" << ", rto="
				<< segInfo.rto.count() << "ms" << std::endl;
	}

	// for segments in retransmission queue, no need to decrement m_nInFlight since
	// it's already been decremented when segments timed out
	if (segInfo.state != SegmentState::InRetxQueue && m_nInFlight > 0) {
		m_nInFlight--;
	}

	m_receivedSize += data.getContent().value_size();
	m_nReceived++;

	increaseWindow();
	onData(interest, data);

	if (segInfo.state == SegmentState::FirstTimeSent || segInfo.state == SegmentState::InRetxQueue) { // do not sample RTT for retransmitted segments
		size_t nExpectedSamples = std::max(static_cast<int>(std::ceil(m_nInFlight / 2.0)), 1);

		time::steady_clock::duration cur = time::steady_clock::now() - m_startTime;
		double now = (double) cur.count() / 1000000000;
		m_rttEstimator.addMeasurement(recvSegNo, now, rtt, nExpectedSamples);
		m_segmentInfo.erase(recvSegNo); // remove the entry associated with the received segment
	}
	else { // retransmission
		segInfo.state = SegmentState::RetxReceived;
	}

	BOOST_ASSERT(m_nReceived > 0);
	if (m_hasFinalBlockId && m_nReceived - 1 >= m_lastSegmentNo) { // all segments have been received
		cancel();
		if (m_options.isVerbose) {
			printSummary();
		}
	}
	else {
		schedulePackets();
	}
}

void PipelineInterestsTcpBic::handleNack(const Interest& interest, const lp::Nack& nack)
{
	if (isStopping())
		return;

	if (m_options.isVerbose)
		std::cerr << "Received Nack with reason " << nack.getReason() << " for Interest " << interest
				<< std::endl;

	uint64_t segNo = interest.getName()[-1].toSegment();

	switch (nack.getReason()) {
	case lp::NackReason::DUPLICATE: {
		break; // ignore duplicates
	}
	case lp::NackReason::CONGESTION: { // treated the same as timeout for now
		m_retxQueue.push(segNo); // put on retx queue
		m_segmentInfo[segNo].state = SegmentState::InRetxQueue; // update state
		handleTimeout(1);
		break;
	}
	default: {
		handleFail(segNo,
				"Could not retrieve data for " + interest.getName().toUri() + ", reason: "
						+ boost::lexical_cast<std::string>(nack.getReason()));
		break;
	}
	}
}

void PipelineInterestsTcpBic::handleLifetimeExpiration(const Interest& interest)
{
	if (isStopping())
		return;

	uint64_t segNo = interest.getName()[-1].toSegment();
	m_retxQueue.push(segNo); // put on retx queue
	m_segmentInfo[segNo].state = SegmentState::InRetxQueue; // update state
	handleTimeout(1);
}

void PipelineInterestsTcpBic::handleTimeout(int timeoutCount)
{
	if (timeoutCount <= 0)
		return;

	if (m_options.disableCwa || m_highData > m_recPoint) {
		// react to only one timeout per RTT (conservative window adaptation)
		m_recPoint = m_highInterest;

		decreaseWindow();
		m_rttEstimator.backoffRto();
		m_nLossEvents++;

		if (m_options.isVerbose) {
			std::cerr << "Packet loss event, cwnd = " << m_cwnd << ", ssthresh = " << m_ssthresh
					<< std::endl;
		}
	}

	if (m_nInFlight > static_cast<uint64_t>(timeoutCount))
		m_nInFlight -= timeoutCount;
	else
		m_nInFlight = 0;

	schedulePackets();
}

void PipelineInterestsTcpBic::handleFail(uint64_t segNo, const std::string& reason)
{
	if (isStopping())
		return;

	// if the failed segment is definitely part of the content, raise a fatal error
	if (m_hasFinalBlockId && segNo <= m_lastSegmentNo)
		return onFailure(reason);

	if (!m_hasFinalBlockId) {
		m_segmentInfo.erase(segNo);
		if (m_nInFlight > 0)
			m_nInFlight--;

		if (m_segmentInfo.empty()) {
			onFailure("Fetching terminated but no final segment number has been found");
		}
		else {
			cancelInFlightSegmentsGreaterThan(segNo);
			m_hasFailure = true;
			m_failedSegNo = segNo;
			m_failureReason = reason;
		}
	}
}

void PipelineInterestsTcpBic::increaseWindow()
{
if (m_cwnd < LOW_WINDOW) {
    // Normal TCP
    if (m_cwnd <= m_ssthresh) {
      m_cwnd = m_cwnd + 1;
    }
    else {
      m_cwnd = m_cwnd + (double) 1.0 / m_cwnd;
    }
  }
  else if (is_bic_ss == false) { // bin. increase
    //      std::cout << "BIC Increase, cwnd: " << m_cwnd << ", bic_target_win: " << bic_target_win << "\n";
    if (bic_target_win - m_cwnd < MAX_INCREMENT) { // binary search
      m_cwnd += (bic_target_win - m_cwnd) / m_cwnd;
    }
    else {
      m_cwnd += MAX_INCREMENT / m_cwnd; // additive increase
    }
    // FIX for equal double values.
    if (m_cwnd + 0.00001 < bic_max_win) {
      //        std::cout << "3 Cwnd: " << m_cwnd << ", bic_max_win: " << bic_max_win << "\n";
      bic_min_win = m_cwnd;
      //        std::cout << "bic_max_win: " << bic_max_win << ", bic_min_win: " << bic_min_win << "\n";
      bic_target_win = (bic_max_win + bic_min_win) / 2;
    }
    else {
//              std::cout
//                  << time::duration_cast<time::milliseconds>(time::steady_clock::now().time_since_epoch())
//                  << " setting BIC SS true\n";
      is_bic_ss = true;
      bic_ss_cwnd = 1;
      bic_ss_target = m_cwnd + 1;
      bic_max_win = MAX_INT;
    }
  }
  // TODO: Some problem. ???
  else { // slow start
    //      std::cout
    //          << time::duration_cast<time::milliseconds>(time::steady_clock::now().time_since_epoch())
    //          << "Entering BIC slow start! cwnd: " << m_cwnd << "\n";
    //      std::cout << "SS BIC Increase, cwnd: " << m_cwnd << ", bic_target_win: " << bic_target_win << "\n";
    m_cwnd += bic_ss_cwnd / m_cwnd;
    if (m_cwnd >= bic_ss_target) {
      bic_ss_cwnd = 2 * bic_ss_cwnd;
      bic_ss_target = m_cwnd + bic_ss_cwnd;
    }
    if (bic_ss_cwnd >= MAX_INCREMENT) {
      is_bic_ss = false;
    }
  }
  afterCwndChange(time::steady_clock::now() - m_startTime, m_cwnd);
}

void PipelineInterestsTcpBic::decreaseWindow()
{
  // BIC Decrease
  if (m_cwnd >= LOW_WINDOW) {
    auto prev_max = bic_max_win;
    bic_max_win = m_cwnd;
    m_cwnd = m_cwnd * m_beta;
    bic_min_win = m_cwnd;
    if (prev_max > bic_max_win) //Fast. Conv.
      bic_max_win = (bic_max_win + bic_min_win) / 2;
    bic_target_win = (bic_max_win + bic_min_win) / 2;
  }
  else {
    // Normal TCP
    m_ssthresh = m_cwnd * 0.5;
    m_cwnd = m_ssthresh;

    //if (resetToInitial) {
    //  m_cwnd = m_initialWindow;
    //}
  }

  if (resetToInitial) {
    m_ssthresh = m_cwnd * 0.5;
    m_cwnd = m_initialWindow;
  }
  afterCwndChange(time::steady_clock::now() - m_startTime, m_cwnd);
}

uint64_t PipelineInterestsTcpBic::getNextSegmentNo()
{
	// get around the excluded segment
	if (m_nextSegmentNo == m_excludedSegmentNo)
		m_nextSegmentNo++;
	return m_nextSegmentNo++;
}

void PipelineInterestsTcpBic::cancelInFlightSegmentsGreaterThan(uint64_t segmentNo)
{
	for (auto it = m_segmentInfo.begin(); it != m_segmentInfo.end();) {
		// cancel fetching all segments that follow
		if (it->first > segmentNo) {
			m_face.removePendingInterest(it->second.interestId);
			it = m_segmentInfo.erase(it);
			if (m_nInFlight > 0)
				m_nInFlight--;
		}
		else {
			++it;
		}
	}
}

void PipelineInterestsTcpBic::printSummary() const
{
	Milliseconds timePassed = time::steady_clock::now() - m_startTime;
	double throughput = (8 * m_receivedSize * 1000) / timePassed.count();

	int pow = 0;
	std::string throughputUnit;
	while (throughput >= 1000.0 && pow < 4) {
		throughput /= 1000.0;
		pow++;
	}
	switch (pow) {
	case 0:
		throughputUnit = "bit/s";
		break;
	case 1:
		throughputUnit = "kbit/s";
		break;
	case 2:
		throughputUnit = "Mbit/s";
		break;
	case 3:
		throughputUnit = "Gbit/s";
		break;
	case 4:
		throughputUnit = "Tbit/s";
		break;
	}

	std::cerr << "\nAll segments have been received.\n" << "Total # of segments received: "
			<< m_nReceived << "\n" << "Time used: " << timePassed.count() << " ms" << "\n"
			<< "Total # of packet loss burst: " << m_nLossEvents << "\n" << "Packet loss rate: "
			<< static_cast<double>(m_nLossEvents) / static_cast<double>(m_nReceived) << "\n"
			<< "Total # of retransmitted segments: " << m_nRetransmitted << "\n" << "Goodput: "
			<< throughput << " " << throughputUnit << "\n";
}

std::ostream&
operator<<(std::ostream& os, SegmentState state)
{
	switch (state) {
	case SegmentState::FirstTimeSent:
		os << "FirstTimeSent";
		break;
	case SegmentState::InRetxQueue:
		os << "InRetxQueue";
		break;
	case SegmentState::Retransmitted:
		os << "Retransmitted";
		break;
	case SegmentState::RetxReceived:
		os << "RetxReceived";
		break;
	}

	return os;
}

std::ostream&
operator<<(std::ostream& os, const PipelineInterestsTcpBicOptions& options)
{
	os << "PipelineInterestsTcpBic initial parameters:" << "\n" << "\tInitial congestion window size = "
			<< options.initCwnd << "\n" << "\tInitial slow start threshold = " << options.initSsthresh
			<< "\n" << "\tMultiplicative decrease factor = " << options.mdCoef << "\n"
			<< "\tAdditive increase step = " << options.aiStep << "\n" << "\tRTO check interval = "
			<< options.rtoCheckInterval << "\n" << "\tMax retries on timeout or Nack = "
			<< options.maxRetriesOnTimeoutOrNack << "\n";

	std::string cwaStatus = options.disableCwa ? "disabled" : "enabled";
	os << "\tConservative Window Adaptation " << cwaStatus << "\n";

	std::string cwndStatus = options.resetCwndToInit ? "initCwnd" : "ssthresh";
	os << "\tResetting cwnd to " << cwndStatus << " when loss event occurs" << "\n";
	return os;
}

} // namespace aimd
} // namespace chunks
} // namespace ndn
