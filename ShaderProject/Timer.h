#pragma once

#include <chrono>
#include <thread>

class Timer 
{
public:
    static void Init();

    static void StartTimer(float seconds);

    static bool IsTimeElapsed();

    static bool IsUsed() { return timer_started; }

private:
    static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    static float duration;
    static bool timer_started;
};

