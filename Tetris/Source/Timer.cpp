#include "Timer.h"

Timer::Timer()
	: timer(), timerSinceStartup(), elapsedTime(0.0f), deltaTime(0.0f) 
{
	Reset();
}

Timer::~Timer()
{}

void Timer::Update()
{
	// Get time elapsed since last frame
	deltaTime = timerSinceStartup.GetElapsedTime();

	// Reset and restart the startup timer for the next frame's delta calculation
	timerSinceStartup.Reset();
	timerSinceStartup.Start();

	// 1. Move current callbacks out so we can safely iterate and modify `delayedCallbacks`
	std::vector<DelayedCallback> activeCallbacks = std::move(delayedCallbacks);
	delayedCallbacks.clear();

	// 2. Process active callbacks
	for (auto& cb : activeCallbacks) {
		cb.currentSeconds += deltaTime;
		if (cb.currentSeconds >= cb.targetSeconds) {
			if (cb.callback) {
				cb.callback(); // If this calls EvokeAfter, it safely pushes to the empty `delayedCallbacks` vector
			}
		}
		else {
			// If it hasn't finished yet, put it back
			delayedCallbacks.push_back(cb);
		}
	}
}

void Timer::Start()
{
	timer.Start();
}

void Timer::Stop()
{
	elapsedTime = timer.GetElapsedTime();

	timer.Stop();
}

void Timer::Reset()
{
	timer.Reset();

	timerSinceStartup.Reset();
	timerSinceStartup.Start();
	elapsedTime = 0.0f;
	
	delayedCallbacks.clear();
}

float Timer::GetElapsedTime() const
{
	return elapsedTime;
}

float Timer::GetDeltaTime() const
{
	return deltaTime;
}

void Timer::EvokeAfter(float seconds, std::function<void()> callback)
{
	if (seconds <= 0.0f) {
		if (callback) callback();
		return;
	}
	delayedCallbacks.push_back({ seconds, 0.0f, callback });
}

Timer::SubTimer::SubTimer()
	: elapsedSeconds(0.0f), running(false) 
{
	Reset();
}

Timer::SubTimer::~SubTimer()
{}

void Timer::SubTimer::Start()
{
	if (!running) {
		startTime = std::chrono::high_resolution_clock::now();
		running = true;
	}
}

void Timer::SubTimer::Stop()
{
	if (running) {
		auto now = std::chrono::high_resolution_clock::now();
		elapsedSeconds += std::chrono::duration<float>(now - startTime).count();
		running = false;
	}
}

void Timer::SubTimer::Reset()
{
	startTime = std::chrono::high_resolution_clock::now();
	elapsedSeconds = 0.0f;
	running = false;
}

float Timer::SubTimer::GetElapsedTime() const
{
	if (running) {
		auto now = std::chrono::high_resolution_clock::now();
		return elapsedSeconds + std::chrono::duration<float>(now - startTime).count();
	}
	return elapsedSeconds;
}
