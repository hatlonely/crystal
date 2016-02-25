//
//  uniqueid_worker.cpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include "uniqueid_worker.h"

namespace uniqueid {

UniqueidHandler::UniqueidHandler() {
    context = Context::instance();
}

void UniqueidHandler::uniqueid(UniqueidResponse &response, const UniqueidRequest &request) {
    std::cout << ToString(request) << std::endl;
    int32_t serial = request.serial;
    int64_t length = request.length;
    std::vector<int64_t> &max_ids = context->get_max_ids();

    response.serial = serial;
    response.offset = max_ids[serial];
    response.length = length;
    if (!context->set_max_id(serial, max_ids[serial] + length)) {
        std::cout << "set max id falied." << std::endl;
    }

    std::cout << ToString(response) << std::endl;
}

}
