//
//  host_ip.cpp
//  code_snips
//
//  Created by hatlonely on 16/7/21.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#pragma once

#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unordered_map>

namespace host_ip {

std::unordered_map<std::string, std::string> HostIps() {
    std::unordered_map<std::string, std::string> result;
    std::string ipv4 = "ipv4";
    std::string ipv6 = "ipv6";
    
    struct ifaddrs * ifaddress = nullptr;
    getifaddrs(&ifaddress);
    char ipbuffer[INET_ADDRSTRLEN];
    while (ifaddress != nullptr) {
        if (ifaddress->ifa_addr->sa_family == AF_INET) {
            void* address = &((struct sockaddr_in *)ifaddress->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, address, ipbuffer, INET_ADDRSTRLEN);
            result[ipv4 + ifaddress->ifa_name] = ipbuffer;
        } else if (ifaddress->ifa_addr->sa_family == AF_INET6) {
            void* address = &((struct sockaddr_in *)ifaddress->ifa_addr)->sin_addr;
            inet_ntop(AF_INET6, address, ipbuffer, INET6_ADDRSTRLEN);
            result[ipv6 + ifaddress->ifa_name] = ipbuffer;
        }

        ifaddress = ifaddress->ifa_next;
    }

    return result;
}
   
std::string HostIp(sa_family_t family=AF_INET) {
    std::string result = "unknow";
    struct ifaddrs * ifaddress = nullptr;
    getifaddrs(&ifaddress);
    char ipbuffer[INET_ADDRSTRLEN];
    while (ifaddress != nullptr) {
        if (ifaddress->ifa_addr->sa_family == family && ifaddress->ifa_name[0] == 'e') {
            void* address = &((struct sockaddr_in *)ifaddress->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, address, ipbuffer, INET_ADDRSTRLEN);
            result = ipbuffer;
        }
        ifaddress = ifaddress->ifa_next;
    }
    
    return result;
}
    
std::string HostIpv4() {
    return HostIp(AF_INET);
}
    
std::string HostIpv6() {
    return HostIp(AF_INET6);
}
    
int main(int argc, const char* argv[]) {
    for (const auto& hostIp : HostIps()) {
        std::cout << hostIp.first << " => " << hostIp.second << std::endl;
    }
    
    std::cout << HostIp() << std::endl;
    std::cout << HostIpv4() << std::endl;
    std::cout << HostIpv6() << std::endl;
    
    return 0;
}
    
}
