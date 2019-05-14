#include "Timer.h"

Timer::Timer() : time(0) {}

void Timer::Update(double dt) {
    time += dt;
}

void Timer::Restart() {
    time = 0;
}

double Timer::Get() {
    return time;
}