//
//  common.cpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include "common.h"
#include <sstream>

namespace uniqueid {

std::string ToString(const UniqueidRequest &request) {
    std::stringstream ss;
    ss << "{";
    ss << "serial: " << request.serial << ", ";
    ss << "length: " << request.length;
    ss << "}";
    return ss.str();
}

std::string ToString(const UniqueidResponse &response) {
    std::stringstream ss;
    ss << "{";
    ss << "serial: " << response.serial << ", ";
    ss << "length: " << response.length << ", ";
    ss << "offset: " << response.offset;
    ss << "}";
    return ss.str();
}

}
