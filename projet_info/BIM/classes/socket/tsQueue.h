//
// Created by benji on 20/11/2022.
//

#ifndef BIM_TSQUEUE_H
#define BIM_TSQUEUE_H


#include <mutex>
#include <thread>
#include <queue>


template <typename T>
class tsQueue {
public:
    tsQueue() = default;
    tsQueue(const tsQueue<T>&) = delete;

    const T& front()
    {
        std::scoped_lock lock(mutexQueue_);
        return queue_.front();
    }

    const T& back()
    {
        std::scoped_lock lock(mutexQueue_);
        return queue_.back();
    }

    T pop()
    {
        std::scoped_lock lock(mutexQueue_);
        auto t = std::move(queue_.front());
        queue_.pop();

        return t;
    }

    T push(const T& item)
    {
        std::scoped_lock lock(mutexQueue_);
        queue_.push(std::move(item));

        std::unique_lock<std::mutex> ul(muxBlocking);
        cvBlocking.notify_one();
    }

    bool empty()
    {
        return queue_.empty();
    }

    void wait()
    {
        while (empty())
        {
            std::unique_lock<std::mutex> ul(muxBlocking);
            cvBlocking.wait(ul);
        }
    }

protected:
    std::mutex mutexQueue_;
    std::queue<T> queue_;
    std::condition_variable cvBlocking;
    std::mutex muxBlocking;
};


#endif //BIM_TSQUEUE_H
