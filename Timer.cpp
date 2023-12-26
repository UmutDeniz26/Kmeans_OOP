#include "Timer.h"
#include <iostream>
#include <iomanip>

Timer::Timer() {}

Timer::~Timer() {}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::end() {
    endTime = std::chrono::high_resolution_clock::now();
}

std::chrono::microseconds Timer::getElapsedTime() {
    return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
}

void Timer::print() {
    std::chrono::microseconds elapsedTime = getElapsedTime();
    double seconds = static_cast<double>(elapsedTime.count()) / 1e6;

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Elapsed time: " << seconds << " seconds" << std::endl;
}
