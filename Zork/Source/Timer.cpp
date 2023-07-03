#include "Timer.h"

Timer::Timer()
{
	Reset();
	timeScale = 1.0f;
	deltaTime = std::chrono::duration<float>(0.0f);
}

Timer::~Timer()
{
}

void Timer::Reset()
{
	startTime = std::chrono::system_clock::now();
}

float Timer::DeltaTime()
{
	return deltaTime.count();
}

void Timer::SetTimeScale(float t)
{
	timeScale = t;
}

float Timer::GetTimeScale()
{
	return timeScale;
}

void Timer::Tick()
{
	deltaTime = std::chrono::system_clock::now() - startTime;
}

