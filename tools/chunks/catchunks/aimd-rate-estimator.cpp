/**
 * Copyright (c) 2016,  Arizona Board of Regents.
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
 * @author Teng Liang
 */

#include "aimd-rate-estimator.hpp"
#include <cmath>

namespace ndn {
namespace chunks {
namespace aimd {

RateEstimator::RateEstimator(double rateInterval)
  : m_rateInterval(rateInterval)
{
}

void
RateEstimator::addMeasurement(double now, uint64_t nPackets, uint64_t nBits)
{
  double pps = nPackets / m_rateInterval;
  double kbps = (nBits / m_rateInterval) / 1000;

  afterRateMeasurement({now, pps, kbps});
}

// std::ostream&
// operator<<(std::ostream& os, double rateInterval)
// {
//   os << "RateEstimator initial parameters:\n"
//      << "\tRate Interval = " << rateInterval << "\n";
//   return os;
// }

} // namespace aimd
} // namespace chunks
} // namespace ndn
