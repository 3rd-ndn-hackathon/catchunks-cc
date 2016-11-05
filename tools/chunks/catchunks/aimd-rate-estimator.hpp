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

#ifndef NDN_TOOLS_CHUNKS_CATCHUNKS_AIMD_RATE_ESTIMATOR_HPP
#define NDN_TOOLS_CHUNKS_CATCHUNKS_AIMD_RATE_ESTIMATOR_HPP

#include "core/common.hpp"

namespace ndn {
namespace chunks {
namespace aimd {

typedef time::duration<double, time::milliseconds::period> Milliseconds;

struct RateSample
{
  double now;
  double pps;
  double kbps;
};

/**
 * @brief Rate Estimator.
 *
 */
class RateEstimator
{
public:


  /**
   * @brief create a RTT Estimator
   *
   * Configures the RTT Estimator with the default parameters if an instance of Options
   * is not passed to the constructor.
   */ 
  explicit
  RateEstimator(double rateInterval);


  void
  addMeasurement(double now, uint64_t nPackets, uint64_t nBits);

  /**
   * @brief Signals after rate is measured
   */
  signal::Signal<RateEstimator, RateSample> afterRateMeasurement;


PUBLIC_WITH_TESTS_ELSE_PRIVATE:
  double m_rateInterval;
};


// std::ostream&
// operator<<(std::ostream& os, double rateInterval);

} // namespace aimd
} // namespace chunks
} // namespace ndn

#endif // NDN_TOOLS_CHUNKS_CATCHUNKS_RTT_ESTIMATOR_HPP
