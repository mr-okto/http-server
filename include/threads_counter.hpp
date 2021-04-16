#ifndef HTTP_SERVER_THREADS_COUNTER_HPP
#define HTTP_SERVER_THREADS_COUNTER_HPP


#include <mutex>

class ThreadsCounter {
public:
    explicit ThreadsCounter(unsigned int limit);
    void inc();
    void dec();
private:
    unsigned int threads_limit_m;
    unsigned int threads_cnt_m;
    bool threads_limit_reached_m;
    std::mutex thread_cnt_mutex_m;
    std::mutex threads_limit_mutex_m;

};


#endif //HTTP_SERVER_THREADS_COUNTER_HPP
