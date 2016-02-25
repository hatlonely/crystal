//
//  common.h
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#ifndef UNIQUEID_COMMON_H
#define UNIQUEID_COMMON_H

#include <string>
#include "gen-cpp/Uniqueid.h"

namespace uniqueid {

const std::string kConfigPath = "config/uniqueid.json";

extern std::string ToString(const UniqueidRequest &request);
extern std::string ToString(const UniqueidResponse &response);

}

#endif // UNIQUEID_COMMON_H
