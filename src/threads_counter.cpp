#include "threads_counter.hpp"

ThreadsCounter::ThreadsCounter(unsigned int limit)
    : threads_limit_m(limit), threads_cnt_m(0),
    threads_limit_reached_m(false) {}

void ThreadsCounter::inc() {
    threads_limit_mutex_m.lock();
    thread_cnt_mutex_m.lock();
    threads_cnt_m++;
    threads_limit_reached_m = threads_cnt_m == threads_limit_m;
    if (!threads_limit_reached_m) {
        threads_limit_mutex_m.unlock();
    }
    thread_cnt_mutex_m.unlock();
}

void ThreadsCounter::dec() {
    thread_cnt_mutex_m.lock();
    if (threads_cnt_m == 0) {
        throw std::runtime_error("Threads counter underflow");
    }
    threads_cnt_m--;
    if (threads_limit_reached_m) {
        threads_limit_mutex_m.unlock();
        threads_limit_reached_m = false;
    }
    thread_cnt_mutex_m.unlock();
}
