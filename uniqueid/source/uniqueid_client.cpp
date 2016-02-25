//
//  uniqueid_client.cpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <random>
#include <thread>
#include <boost/make_shared.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <glog/logging.h>
#include "gen-cpp/Uniqueid.h"
#include "common.h"

void process() {
    for (int i = 0; i < 100; i++) {
        typedef ::apache::thrift::transport::TTransport TTransport;
        typedef ::apache::thrift::transport::TSocket TSocket;
        typedef ::apache::thrift::protocol::TProtocol TProtocol;
        typedef ::apache::thrift::transport::TBufferedTransport TBufferedTransport;
        typedef ::apache::thrift::protocol::TBinaryProtocol TBinaryProtocol;
        typedef ::apache::thrift::TException TException;
        boost::shared_ptr<TTransport> socket    = boost::make_shared<TSocket>("127.0.0.1", 9090);
        boost::shared_ptr<TTransport> transport = boost::make_shared<TBufferedTransport>(socket);
        boost::shared_ptr<TProtocol> protocol   = boost::make_shared<TBinaryProtocol>(transport);
        uniqueid::UniqueidClient client(protocol);
        
        try {
            std::random_device rd;
            transport->open();
            uniqueid::UniqueidRequest request;
            uniqueid::UniqueidResponse response;
            request.logid = rd();
            request.serial = rd() % 10;
            request.length = rd() % 10;
            client.uniqueid(response, request);
            LOG(INFO) << ToString(response);
            transport->close();
        } catch (TException &te) {
            LOG(FATAL) << te.what();
        }
    }
}

int main(int argc, const char *argv[]) {
    std::thread threads[10];
    for (int i = 0; i < 10; i ++) {
        threads[i] = std::thread(process);
    }
    for (int i = 0; i < 10; i++) {
        threads[i].join();
    }

    return 0;
}
