#!/usr/bin/env python3
#coding: utf-8

import sys
import thriftpy
import random
from thriftpy.rpc import make_client

def main():
    host            = '127.0.0.1' if len(sys.argv) < 2 else sys.argv[1]
    port            = 9090 if len(sys.argv) < 3 else int(sys.argv[2])
    uniqueid_thrift = thriftpy.load('../protocol/uniqueid.thrift', module_name='uniqueid_thrift')
    client          = make_client(uniqueid_thrift.Uniqueid, host, port)
    request         = uniqueid_thrift.UniqueidRequest()
    request.logid   = random.randint(-2147483648, 2147483647)
    request.serial  = random.randint(0, 9)
    request.length  = random.randint(1, 10)
    response        = client.uniqueid(request)
    print(response)

if __name__ == '__main__':
    main()
