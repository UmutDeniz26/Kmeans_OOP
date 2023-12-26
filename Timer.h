#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    Timer();
    ~Timer();

    void start();
    void end();
    void print();

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

    std::chrono::microseconds getElapsedTime();
};

#endif // TIMER_H
