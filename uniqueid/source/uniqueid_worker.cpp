//
//  uniqueid_worker.cpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include "uniqueid_worker.h"
#include <glog/logging.h>

namespace uniqueid {

void UniqueidHandler::uniqueid(UniqueidResponse &response, const UniqueidRequest &request) {
    Context *context = Context::instance();

    int32_t serial = request.serial;
    int64_t length = request.length;
    std::lock_guard<std::mutex>(context->get_mutexs(serial));
    std::vector<int64_t> &max_ids = context->get_max_ids();

    response.serial = serial;
    response.offset = max_ids[serial];
    response.length = length;
    if (!context->set_max_id(serial, max_ids[serial] + length)) {
        LOG(FATAL) << "[logid: " << (uint32_t)request.logid << "] set max id failed.";
        UniqueidException ue;
        ue.status = ResStatus::kRSFail;
        ue.what = "set max id failed.";
        throw ue;
    }

    LOG(INFO) << "host [" << _sock->getPeerAddress() << ":" << _sock->getPeerPort() << "], "
              << "logid [" << (uint32_t)request.logid << "], "
              << "request [" << ToString(request) << "], "
              << "response [" << ToString(response) << "]";
}

}
