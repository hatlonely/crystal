//
//  main.cpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <sstream>

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
#include "uniqueid_worker.h"

int main(int argc, const char * argv[]) {
    typedef ::apache::thrift::TProcessor TProcessor;
    typedef ::apache::thrift::TProcessorFactory TProcessorFactory;
    typedef ::apache::thrift::transport::TServerTransport TServerTransport;
    typedef ::apache::thrift::transport::TServerSocket TServerSocket;
    typedef ::apache::thrift::transport::TTransportFactory TTransportFactory;
    typedef ::apache::thrift::transport::TBufferedTransportFactory TBufferedTransportFactory;
    typedef ::apache::thrift::protocol::TProtocolFactory TProtocolFactory;
    typedef ::apache::thrift::protocol::TBinaryProtocolFactory TBinaryProtocolFactory;
    typedef ::apache::thrift::server::TSimpleServer TSimpleServer;
    typedef ::apache::thrift::server::TThreadedServer TThreadedServer;
    typedef ::apache::thrift::server::TThreadPoolServer TThreadPoolServer;
    typedef ::apache::thrift::concurrency::ThreadManager ThreadManager;
    typedef ::apache::thrift::concurrency::ThreadFactory ThreadFactory;
    typedef ::apache::thrift::concurrency::PlatformThreadFactory PlatformThreadFactory;

    boost::property_tree::ptree &config = uniqueid::Context::instance()->get_config();
    const int server_port  = config.get<int32_t>("server_port");
    const int worker_count = config.get<int32_t>("worker_count");
    boost::shared_ptr<ThreadManager> thread_manager = ThreadManager::newSimpleThreadManager(worker_count);
    boost::shared_ptr<ThreadFactory> thread_factory = boost::make_shared<PlatformThreadFactory>();
    thread_manager->threadFactory(thread_factory);
    thread_manager->start();

    boost::shared_ptr<uniqueid::UniqueidIfFactory> if_factory = boost::make_shared<uniqueid::UniqueidCloneFactory>();
    boost::shared_ptr<TProcessorFactory> processor            = boost::make_shared<uniqueid::UniqueidProcessorFactory>(if_factory);
    boost::shared_ptr<TServerTransport> server_transport      = boost::make_shared<TServerSocket>(server_port);
    boost::shared_ptr<TTransportFactory> transport_factory    = boost::make_shared<TBufferedTransportFactory>();
    boost::shared_ptr<TProtocolFactory> protocol_factory      = boost::make_shared<TBinaryProtocolFactory>();
    TThreadPoolServer server(processor, server_transport, transport_factory, protocol_factory, thread_manager);
    server.serve();

    return 0;
}
