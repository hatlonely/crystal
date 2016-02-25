//
//  uniqueid_worker.h
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#ifndef UNIQUEID_UNIQUEID_WORKER_H
#define UNIQUEID_UNIQUEID_WORKER_H

#include <iostream>
#include <boost/make_shared.hpp>
#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PlatformThreadFactory.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>
#include "gen-cpp/Uniqueid.h"
#include "common.h"
#include "context.h"

namespace uniqueid {

class UniqueidHandler : virtual public UniqueidIf {
public:
    UniqueidHandler();
    void uniqueid(UniqueidResponse &response, const int32_t logid, const UniqueidRequest &request);

private:
    Context *context;
};

class UniqueidCloneFactory : public ::uniqueid::UniqueidIfFactory {
public:
    virtual ~UniqueidCloneFactory() {}
    virtual ::uniqueid::UniqueidIf *getHandler(const ::apache::thrift::TConnectionInfo &connInfo) {
        typedef ::apache::thrift::transport::TSocket TSocket;
        boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(connInfo.transport);
        return new UniqueidHandler;
    }
    virtual void releaseHandler(::uniqueid::UniqueidIf *handler) {
        delete handler;
    }
};

}  // namespace uniqueid

#endif // UNIQUEID_UNIQUEID_WORKER_H
