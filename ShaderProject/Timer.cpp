#include "Timer.h"

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::start_time;
float Timer::duration;
bool Timer::timer_started;

void Timer::Init()
{
    start_time = std::chrono::high_resolution_clock::now();
    duration = 0;
    timer_started = false;

}

void Timer::StartTimer(float seconds)
{
    duration = seconds;		//指定時間
    timer_started = true;	//使用フラグ
    start_time = std::chrono::high_resolution_clock::now();		//現状時間の把握
}

bool Timer::IsTimeElapsed()
{
    if (!timer_started)
        return false;

    auto current_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration<float>(current_time - start_time).count();

    if (elapsed_time >= duration)    timer_started = false;

    return elapsed_time >= duration;
}
