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
    typedef ::apache::thrift::transport::TSocket TSocket;
public:
    UniqueidHandler(boost::shared_ptr<TSocket> sock) : _sock(sock) {}
    void uniqueid(UniqueidResponse &response, const UniqueidRequest &request);
private:
    boost::shared_ptr<TSocket> _sock;
};

class UniqueidCloneFactory : public ::uniqueid::UniqueidIfFactory {
public:
    virtual ~UniqueidCloneFactory() {}
    virtual ::uniqueid::UniqueidIf *getHandler(const ::apache::thrift::TConnectionInfo &conn_info) {
        typedef ::apache::thrift::transport::TSocket TSocket;
        boost::shared_ptr<TSocket> sock = boost::dynamic_pointer_cast<TSocket>(conn_info.transport);
        return new UniqueidHandler(sock);
    }
    virtual void releaseHandler(::uniqueid::UniqueidIf *handler) {
        delete handler;
    }
};

}  // namespace uniqueid

#endif // UNIQUEID_UNIQUEID_WORKER_H
