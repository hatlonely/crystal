//
//  join_to_string.cpp
//  code_snips
//
//  Created by hatlonely on 16/6/13.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

namespace join_to_string {

namespace join_to_string_v1 {

template <typename T>
std::string JoinToString(const T& container) {
    std::stringstream os;
    for (const auto& element : container) {
        os << element << ", ";
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - 2, 2);
    }
    return result;
}

int main(int argc, const char* argv[]) {
    std::vector<int> vi = {1, 2, 3, 4};
    std::cout << "[" << JoinToString(vi) << "]" << std::endl;   // [1, 2, 3, 4]
    
    return 0;
}

} // join_to_string_v1

namespace join_to_string_v2 {

// 使用迭代器作为模板打印一个数组区间，增加灵活性
template <typename Iterator>
std::string JoinToString(Iterator begin, Iterator end) {
    std::stringstream os;
    for (auto it = begin; it != end; ++it) {
        os << *it << ", ";
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - 2, 2);
    }
    return result;
}
    
int main(int argc, const char* argv[]) {
    std::vector<int> vi = {1, 2, 3, 4};
    std::cout << "[" << JoinToString(vi.begin(), vi.end()) << "]" << std::endl;     // [1, 2, 3, 4]
    std::cout << "[" << JoinToString(vi.begin() + 1, vi.end()) << "]" << std::endl; // [2, 3, 4]
    
    return 0;
}

} // join_to_string_v2
    
namespace join_to_string_v3 {

#ifndef MAKE_JOIN_STRING_HELPER
#define MAKE_JOIN_STRING_HELPER(Class, Type, field) \
    struct JoinToStringHelper_##Class##_##field { \
        const Type& operator()(const Class& t) { \
        return t.field; \
    } \
};
#endif
    
template <typename T>
struct JoinToStringHelper {
    const T& operator()(const T& t) {
        return t;
    }
};

// 增加函数模板参数，支持打印类的某些字段
template <typename Iterator, typename Function=JoinToStringHelper<typename Iterator::value_type>>
std::string JoinToString(Iterator begin, Iterator end, Function function=Function()) {
    std::stringstream os;
    for (auto it = begin; it != end; ++it) {
        os << function(*it) << ", ";
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - 2, 2);
    }
    return result;
}
    
int main(int argc, const char* argv[]) {
    {
        std::vector<int> vi = {1, 2, 3, 4};
        std::cout << "[" << JoinToString(vi.begin(), vi.end()) << "]" << std::endl; // [1, 2, 3, 4]
    } {
        struct A {
            int i;
            int j;
        };
        
        MAKE_JOIN_STRING_HELPER(A, int, i);
        MAKE_JOIN_STRING_HELPER(A, int, j);
        
        std::vector<A> va = {{1, 11}, {2, 22}, {3, 33}};
        std::cout << "[" << JoinToString(va.begin(), va.end(), JoinToStringHelper_A_i()) << "]"
                << std::endl;       // [1, 2, 3]
        std::cout << "[" << JoinToString(va.begin(), va.end(), JoinToStringHelper_A_j()) << "]"
                << std::endl;       // [11, 22, 33]
    }
    
    return 0;
}
    
} // join_to_string_v3
    
namespace join_to_string_v4 {
    
#ifndef MAKE_JOIN_STRING_HELPER
#define MAKE_JOIN_STRING_HELPER(Class, Type, field) \
    struct JoinToStringHelper_##Class##_##field { \
        const Type& operator()(const Class& t) { \
        return t.field; \
    } \
};
#endif
    
template <typename T>
struct JoinToStringHelper {
    const T& operator()(const T& t) {
        return t;
    }
};

// 增加separator参数，支持分隔符设置
template <typename Iterator, typename Function=JoinToStringHelper<typename Iterator::value_type>>
std::string JoinToString(Iterator begin, Iterator end,
                         std::string separator=", ", Function function=Function()) {
    std::stringstream os;
    for (auto it = begin; it != end; ++it) {
        os << function(*it) << separator;
    }
    std::string result = os.str();
    if (!result.empty()) {
        result.erase(result.length() - separator.length(), separator.length());
    }
    return result;
}

int main(int argc, const char* argv[]) {
    {
        std::vector<int> vi = {1, 2, 3, 4};
        std::cout << "[" << JoinToString(vi.begin(), vi.end()) << "]" << std::endl;      // [1, 2, 3, 4]
        std::cout << "[" << JoinToString(vi.begin(), vi.end(), "|") << "]" << std::endl; // [[1|2|3|4]
    } {
        struct A {
            int i;
            int j;
        };
        
        MAKE_JOIN_STRING_HELPER(A, int, i);
        MAKE_JOIN_STRING_HELPER(A, int, j);
        
        std::vector<A> va = {{1, 11}, {2, 22}, {3, 33}};
        std::cout << "[" << JoinToString(va.begin(), va.end(), ", ", JoinToStringHelper_A_i()) << "]"
            << std::endl;       // [1, 2, 3]
        std::cout << "[" << JoinToString(va.begin(), va.end(), ", ", JoinToStringHelper_A_j()) << "]"
            << std::endl;       // [11, 22, 33]
    }
    
    return 0;
}
    
} // join_to_string_v4

int main(int argc, const char* argv[]) {
    join_to_string_v1::main(argc, argv);
    join_to_string_v2::main(argc, argv);
    join_to_string_v3::main(argc, argv);
    join_to_string_v4::main(argc, argv);
    
    return 0;
}

}
