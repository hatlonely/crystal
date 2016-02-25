//
//  context.cpp
//  uniqueid
//
//  Created by hatlonely on 16/2/24.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#include "context.h"
#include <fstream>
#include <exception>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <glog/logging.h>
#include "common.h"

namespace uniqueid {
    
int Context::init() {
    static bool is_inited = false;
    if (is_inited) {
        return 0;
    }
    
    boost::filesystem::ifstream ifs(kConfigPath);
    if (!ifs.good()) {
        LOG(FATAL) << "open config file [" << kConfigPath << "] failed.";
        return -1;
    }
    boost::property_tree::read_json(ifs, _config);
    
    int32_t serials_size = _config.get<int32_t>("serials_size");
    _max_ids = std::vector<int64_t>(serials_size, 0);
    
    _serials_file_path = _config.get<std::string>("serials_file");
    if (!boost::filesystem::exists(_serials_file_path)) {
        boost::filesystem::ofstream serials_file(_serials_file_path, std::ios::binary);
        if (!serials_file.good()) {
            throw new std::exception();
        }
        int64_t max_id = 0;
        for (int i = 0; i < serials_size; i++) {
            serials_file.write((char *)&max_id, sizeof(max_id));
        }
        serials_file.close();
    }
    
    if (boost::filesystem::file_size(_serials_file_path) < serials_size * sizeof(int64_t)) {
        boost::filesystem::ofstream serials_file(_serials_file_path, std::ios::binary | std::ios::app);
        if (!serials_file.good()) {
            LOG(FATAL) << "open serials file [" << _serials_file_path.string() << "] failed.";
            return -1;
        }
        char zero = 0;
        for (int i = boost::filesystem::file_size(_serials_file_path); i < serials_size * sizeof(int64_t); i++) {
            serials_file.write(&zero, sizeof(zero));
        }
        serials_file.close();
    }
    
    {
        boost::filesystem::ifstream serials_file(_serials_file_path, std::ios::binary);
        if (!serials_file.good()) {
            LOG(FATAL) << "open serials file [" << _serials_file_path.string() << "] failed.";
            return -1;        }
        for (int i = 0; i < serials_size; i++) {
            serials_file.read((char *)&_max_ids[i], sizeof(int64_t));
        }
        serials_file.close();
    }
    
    is_inited = true;
    
    return 0;
}

bool Context::set_max_id(int32_t serial, int64_t max_id) {
    if (serial < 0 || serial >= _max_ids.size()) {
        LOG(WARNING) << "serial [" << serial << "] not found";
        return false;
    }

    boost::filesystem::fstream serials_file(_serials_file_path, std::ios::binary | std::ios::in | std::ios::out);
    if (!serials_file.good()) {
        LOG(FATAL) << "open serials file [" << _serials_file_path.string() << "] failed.";
        return false;
    }

    serials_file.seekp(serial * sizeof(int64_t));
    serials_file.write((char *)&max_id, sizeof(max_id));
    serials_file.close();

    _max_ids[serial] = max_id;

    return true;
}

}
