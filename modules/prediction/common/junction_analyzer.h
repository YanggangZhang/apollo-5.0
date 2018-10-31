/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "modules/map/hdmap/hdmap_common.h"
#include "modules/prediction/proto/feature.pb.h"
#include "modules/prediction/common/prediction_map.h"

namespace apollo {
namespace prediction {

class JunctionAnalyzer {
 public:
  /**
   * @brief Initialize by junction ID, if junction id differs from prev cycle
   * @param junction ID
   */
  static void Init(const std::string& junction_id);

  /**
   * @brief Clear all stored data
   */
  static void Clear();

  /**
   * @brief Get all filtered junction exits associated to start lane ID
   * @param start lane ID
   * @return Filtered junction exits
   */
  std::vector<JunctionExit> GetJunctionExits(const std::string& start_lane_id);

 private:
  /**
   * @brief Set all junction exits in the hashtable junction_exits_
   */
  static void SetAllJunctionExits();

  /**
   * @brief Determine if a lane with lane_id is an exit lane of this junction
   * @param lane ID
   * @return If a lane with lane_id is an exit lane of this junction
   */
  static bool IsExitLane(const std::string& lane_id);

 private:
  // junction_info pointer associated to the input junction_id
  static std::shared_ptr<const apollo::hdmap::JunctionInfo> junction_info_ptr_;
  // Hashtable: exit_lane_id -> junction_exit
  static std::unordered_map<std::string, JunctionExit> junction_exits_;
  // Hashtable: start_lane_id -> junction_feature
  static std::unordered_map<std::string, JunctionFeature> junction_features_;
};

}  // namespace prediction
}  // namespace apollo