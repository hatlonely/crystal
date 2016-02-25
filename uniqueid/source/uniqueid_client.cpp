//
//  uniqueid_client.cpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include <iostream>
#include <boost/make_shared.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include "gen-cpp/Uniqueid.h"
#include "common.h"

int main(int argc, const char *argv[]) {
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
        transport->open();
        uniqueid::UniqueidRequest request;
        uniqueid::UniqueidResponse response;
        request.logid = 1234;
        request.serial = argc > 1 ? atoi(argv[1]) : 1;
        request.length = argc > 2 ? atoi(argv[2]) : 1;
        client.uniqueid(response, request);
        std::cout << ToString(response) << std::endl;
        transport->close();
    } catch (TException &te) {
        std::cout << te.what() << std::endl;
    }

    return 0;
}
