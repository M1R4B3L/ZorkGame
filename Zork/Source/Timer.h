#pragma once

#include <chrono>

class Timer
{
public:

	Timer();
	~Timer();

	void Reset();
	float DeltaTime();
	void SetTimeScale(float t);
	float GetTimeScale();
	void Tick();

public:
	std::chrono::system_clock::time_point startTime;
	std::chrono::duration<float> deltaTime;
	float timeScale;
};