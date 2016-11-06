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
 * @author Weiwei Liu
 */

#include "aimd-statistics-collector.hpp"

namespace ndn {
namespace chunks {
namespace aimd {

StatisticsCollector::StatisticsCollector(PipelineInterestsAimd& pipeline,
                                         RttEstimator& rttEstimator,
                                         RateEstimator& rateEstimator,
                                         std::ostream& osCwnd,
                                         std::ostream& osRtt,
                                         std::ostream& osRate)
  : m_osCwnd(osCwnd)
  , m_osRtt(osRtt)
  , m_osRate(osRate)
{
  m_osCwnd << "time\tcwndsize\n";
  m_osRtt  << "segment\ttime\trtt\trttvar\tsrtt\trto\n";
  m_osRate << "time\tpps\tkbps\n";
  pipeline.afterCwndChange.connect(
    [this] (Milliseconds timeElapsed, double cwnd) {
      m_osCwnd << timeElapsed.count() / 1000 << '\t' << cwnd << '\n';
    });
  rttEstimator.afterRttMeasurement.connect(
    [this] (const RttRtoSample& rttSample) {
      m_osRtt << rttSample.segNo << '\t'
              << rttSample.now << '\t'
              << rttSample.rtt.count() << '\t'
              << rttSample.rttVar.count() << '\t'
              << rttSample.sRtt.count() << '\t'
              << rttSample.rto.count() << '\n';
    });
  rateEstimator.afterRateMeasurement.connect(
    [this] (const RateSample& rateSample) {
      m_osRate << rateSample.now << '\t'
               << rateSample.pps << '\t'
               << rateSample.kbps << '\n';
    });
}

StatisticsCollector::StatisticsCollector(PipelineInterestsCubic& pipeline,
                                         RttEstimator& rttEstimator,
                                         RateEstimator& rateEstimator,
                                         std::ostream& osCwnd,
                                         std::ostream& osRtt,
                                         std::ostream& osRate)
  : m_osCwnd(osCwnd)
  , m_osRtt(osRtt)
  , m_osRate(osRate)
{
  m_osCwnd << "time\tcwndsize\n";
  m_osRtt  << "segment\ttime\trtt\trttvar\tsrtt\trto\n";
  m_osRate << "time\tpps\tkbps\n";
  pipeline.afterCwndChange.connect(
    [this] (Milliseconds timeElapsed, double cwnd) {
      m_osCwnd << timeElapsed.count() / 1000 << '\t' << cwnd << '\n';
    });
  rttEstimator.afterRttMeasurement.connect(
    [this] (const RttRtoSample& rttSample) {
     m_osRtt << rttSample.segNo << '\t'
             << rttSample.now << '\t'
             << rttSample.rtt.count() << '\t'
             << rttSample.rttVar.count() << '\t'
             << rttSample.sRtt.count() << '\t'
             << rttSample.rto.count() << '\n';
    });
  rateEstimator.afterRateMeasurement.connect(
    [this] (const RateSample& rateSample) {
      m_osRate << rateSample.now << '\t'
               << rateSample.pps << '\t'
               << rateSample.kbps << '\n';
    });
}

StatisticsCollector::StatisticsCollector(PipelineInterestsTcpBic& pipeline,
                                         RttEstimator& rttEstimator,
                                         RateEstimator& rateEstimator,
                                         std::ostream& osCwnd,
                                         std::ostream& osRtt,
                                         std::ostream& osRate)
  : m_osCwnd(osCwnd)
  , m_osRtt(osRtt)
  , m_osRate(osRate)
{
  m_osCwnd << "time\tcwndsize\n";
  m_osRtt  << "segment\ttime\trtt\trttvar\tsrtt\trto\n";
  m_osRate << "time\tpps\tkbps\n";
  pipeline.afterCwndChange.connect(
    [this] (Milliseconds timeElapsed, double cwnd) {
      m_osCwnd << timeElapsed.count() / 1000 << '\t' << cwnd << '\n';
    });
  rttEstimator.afterRttMeasurement.connect(
    [this] (const RttRtoSample& rttSample) {
     m_osRtt << rttSample.segNo << '\t'
             << rttSample.now << '\t'
             << rttSample.rtt.count() << '\t'
             << rttSample.rttVar.count() << '\t'
             << rttSample.sRtt.count() << '\t'
             << rttSample.rto.count() << '\n';
    });
  rateEstimator.afterRateMeasurement.connect(
    [this] (const RateSample& rateSample) {
      m_osRate << rateSample.now << '\t'
               << rateSample.pps << '\t'
               << rateSample.kbps << '\n';
    });
}

} // namespace aimd
} // namespace chunks
} // namespace ndn