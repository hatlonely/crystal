//
//  blocking_unordered_map.hpp
//  code_snips
//
//  Created by hatlonely on 16/6/17.
//
//  阻塞队列v1，线程安全 map，继承自 unordered_map，添加 blockingSet 和 blockGet 两个函数
//  阻塞队列v2，线程安全 map，用多个 unordered_map，缩小锁粒度，提高性能

#pragma once

#include <boost/unordered_map.hpp>
#include <boost/thread.hpp>

namespace blocking_unordered_map {

namespace blocking_unordered_map_v1 {

template <typename K, typename V, typename H=std::hash<K>>
class BlockingUnorderedMap : public boost::unordered_map<K, V, H> {
public:
    void blockingSet(const K& key, const V& value) {
        boost::unique_lock<boost::shared_mutex> unique_lock(_mutex);
        (*this)[key] = value;
    }
    
    bool blockingGet(const K& key, V& value) {
        boost::shared_lock<boost::shared_mutex> shared_lock(_mutex);
        typename boost::unordered_map<K, V>::iterator it = this->find(key);
        
        if (it == this->end()) {
            return false;
        }
        
        value = (*this)[key];
        return true;
    }

private:
    boost::shared_mutex _mutex;
};
    
} // blocking_unordered_map_1
    
namespace blocking_unordered_map_v2 {
    
template <typename K, typename V, typename H=std::hash<K>>
class BlockingUnorderedMap {
public:
    explicit BlockingUnorderedMap(size_t size=1, const H& hasher=H()) : _size(size), _hasher(hasher) {
        _mutexs = new boost::shared_mutex[size];
        _maps   = new boost::unordered_map<K, V, H>[size];
    }
    
    virtual ~BlockingUnorderedMap() {
        delete[] _mutexs;
        delete[] _maps;
    }
    
    void blockingSet(const K& key, const V& value) {
        size_t index = _hasher(key) % _size;
        boost::unique_lock<boost::shared_mutex> unique_lock(_mutexs[index]);
        _maps[index][key] = value;
    }
    
    bool blockingGet(const K& key, V& value) {
        size_t index = _hasher(key) % _size;
        boost::shared_lock<boost::shared_mutex> shared_lock(_mutexs[index]);
        typename boost::unordered_map<K, V>::iterator it = _maps[index].find(key);
        
        if (it == _maps[index].end()) {
            return false;
        }
        
        value = _maps[index][key];
        return true;
    }
    
protected:
    boost::shared_mutex* _mutexs;
    boost::unordered_map<K, V, H>* _maps;
    const H _hasher;
    size_t _size;
};
    
} // blocking_unordered_map_v2

int main(int argc, const char* argv[]) {
    blocking_unordered_map_v2::BlockingUnorderedMap<std::string, std::string> bss;
    {
        std::string key = "key";
        std::string value = "value";
        bss.blockingSet(key, value);
    } {
        std::string key = "key";
        std::string value;
        assert(bss.blockingGet(key, value));
        std::cout << value << std::endl;
    }
    
    return 0;
}
    
}