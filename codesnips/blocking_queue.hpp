//
//  blocking_queue.hpp
//  code_snips
//
//  Created by hatlonely on 16/6/13.
//  Copyright © 2016年 hatlonely. All rights reserved.
//

#pragma once

#include <list>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <boost/thread.hpp>

namespace blocking_queue {

template <typename Element>
class BlockingQueue {
public:
    explicit BlockingQueue(const size_t max_queue_size=kMaxQueueSize) :
        _max_queue_size(max_queue_size) {
        // nothing to do
    }

    virtual ~BlockingQueue() {
        // nothing to do
    }

    bool offer(const Element& element, uint64_t timeout_us) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        // 如果队列已满先释放_op_mutex，以便take和poll从队列中取走元素
        // 阻塞等待timeout_us时间，直到队列不满，或者超时返回false
        while (full()) {
            if (!_not_full.timed_wait(op_lock, boost::posix_time::microseconds(timeout_us))) {
                return false;
            }
        }

        // 在从_not_full被唤醒 到 拿到_op_mutex锁之间的时间内队列可能又已经满了
        // 此时直接返回false
        if (full()) {
            return false;
        }
        _list.push_back(element);
        _not_empty.notify_one();
        
        return true;
    }
    
    bool poll(Element& element, uint64_t timeout_us) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        // 如果队列为空先释放_op_mutex，以便put和offer给队列中插入元素
        // 阻塞等待timeout_us时间，直到队列非空，或者超时返回false
        if (empty()) {
            if (!_not_empty.timed_wait(op_lock, boost::posix_time::microseconds(timeout_us))) {
                return false;
            }
        }
        
        // 在从_not_empty被唤醒 到 拿到_op_mutex锁之间的时间内队列可能又空了
        // 此时直接返回false
        if (empty()) {
            return false;
        }
        element = _list.front();
        _list.pop_front();
        _not_full.notify_one();
        
        return true;
    }
    
    void put(const Element& element) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        while (full()) {
            _not_full.wait(op_lock);
        }
        _list.push_back(element);
        _not_empty.notify_one();
    }
    
    void take(Element& element) {
        boost::mutex::scoped_lock op_lock(_op_mutex);
        while (empty()) {
            _not_empty.wait(op_lock);
        }
        element = _list.front();
        _list.pop_front();
        _not_full.notify_one();
    }
    
    bool full() {
        return _list.size() == _max_queue_size;
    }
    
    bool empty() {
        return _list.empty();
    }
    
    size_t size() {
        return _list.size();
    }
    
private:
    static const size_t kMaxQueueSize = 60000;
    
    size_t _max_queue_size;
    std::list<Element> _list;
    boost::mutex _op_mutex;     // 所有对队列的操作都需要获得该锁
    boost::condition_variable _not_empty;   // 队列非空条件
    boost::condition_variable _not_full;    // 队列不满条件
};
    
int main(int argc, const char* argv[]) {
    BlockingQueue<int> bq(10);

    const int kProducerNum = 10;
    const int kConsumerNum = 3;
    std::atomic<int> produce_num(0);
    std::atomic<int> consume_num(0);
    std::atomic<int> total(200);
    std::thread producer[kProducerNum];
    std::thread consumer[kConsumerNum];

    for (int i = 0; i < kProducerNum; i++) {
        producer[i] = std::thread([&](int index) {
            while (++produce_num < total) {
                int element = i;
                while (!bq.offer(element, 100)) {
                    // printf("full wait for consume\n");
                }
                printf("%d produce %d\n", index, i);
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
        }, i);
    }

    for (int i = 0; i < kConsumerNum; i++) {
        consumer[i] = std::thread([&](int index) {
            while (++consume_num < total) {
                int element = 0;
                while (!bq.poll(element, 100)) {
                    // printf("empty wait for produce\n");
                }
                printf("%d consume %d\n", index, i);
            }
        }, i);
    }

    for (int i = 0; i < kProducerNum; i++) {
        producer[i].join();
    }
    for (int i = 0; i < kConsumerNum; i++) {
        consumer[i].join();
    }

    return 0;
}

}
