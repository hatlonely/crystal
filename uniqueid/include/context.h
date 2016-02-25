//
//  context.hpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#ifndef UNIQUEID_CONTEXT_H
#define UNIQUEID_CONTEXT_H

#include <vector>
#include <string>
#include <thread>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

namespace uniqueid {

class Context {
public:
    int init();

    static Context *instance() {
        static Context *context = new Context();
        return context;
    }

    std::vector<int64_t> &get_max_ids() {
        return _max_ids;
    }

    boost::property_tree::ptree &get_config() {
        return _config;
    }

    bool set_max_id(int32_t serial, int64_t max_id);

private:
    Context() = default;
    Context(const Context&) = delete;
    ~Context();

private:
    boost::property_tree::ptree _config;
    std::vector<int64_t> _max_ids;
    boost::filesystem::path _serials_file_path;
};

}

#endif // UNIQUEID_CONTEXT_H
