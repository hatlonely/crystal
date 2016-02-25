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
#include "common.h"

namespace uniqueid {

Context::Context() {
    boost::filesystem::ifstream ifs(kConfigPath);
    if (!ifs.good()) {
        std::cout << "open config file failed." << std::endl;
    }
    boost::property_tree::read_json(ifs, _config);

    int32_t serials_size = _config.get<int32_t>("serials_size");
    _max_ids = std::vector<int64_t>(serials_size, 0);

    _serials_file = _config.get<std::string>("serials_file");
    boost::filesystem::path path(_serials_file);
    if (!boost::filesystem::exists(path)) {
        boost::filesystem::ofstream serials_file(path, std::ios::binary);
        if (!serials_file.good()) {
            throw new std::exception();
        }
        int64_t max_id = 0;
        for (int i = 0; i < serials_size; i++) {
            serials_file.write((char *)&max_id, sizeof(max_id));
        }
        serials_file.close();
    }

    if (boost::filesystem::file_size(path) < serials_size * sizeof(int64_t)) {
        boost::filesystem::ofstream serials_file(path, std::ios::binary | std::ios::app);
        if (!serials_file.good()) {
            std::cout << "open serials file failed." << std::endl;
            throw new std::exception();
        }
        char zero = 0;
        for (int i = boost::filesystem::file_size(path); i < serials_size * sizeof(int64_t); i++) {
            serials_file.write(&zero, sizeof(zero));
        }
        serials_file.close();
    }

    {
        boost::filesystem::ifstream serials_file(path, std::ios::binary);
        if (!serials_file.good()) {
            std::cout << "open serials file failed." << std::endl;
            throw new std::exception();
        }
        for (int i = 0; i < serials_size; i++) {
            serials_file.read((char *)&_max_ids[i], sizeof(int64_t));
        }
        serials_file.close();
    }
}

bool Context::set_max_id(int32_t serial, int64_t max_id) {
    if (serial < 0 || serial >= _max_ids.size()) {
        std::cout << "serial not found" << std::endl;
        return false;
    }

    boost::filesystem::path path(_serials_file);
    boost::filesystem::fstream serials_file(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!serials_file.good()) {
        std::cout << "open serials_file failed.";
        return false;
    }

    serials_file.seekp(serial * sizeof(int64_t));
    serials_file.write((char *)&max_id, sizeof(max_id));
    serials_file.close();

    _max_ids[serial] = max_id;
    std::cout << _max_ids[serial] << std::endl;

    return true;
}

}
