#pragma once

#include <chrono>
#include <vector>
#include <functional>


class Timer
{
public:
	Timer();
	~Timer();

	void Update();
	
	void Start();
	void Stop();
	void Reset();
	float GetElapsedTime() const;
	float GetDeltaTime() const;

	void EvokeAfter(float seconds, std::function<void()> callback);
private:
	class SubTimer
	{
	public:
		SubTimer();
		~SubTimer();

		void Start();
		void Stop();
		void Reset();
		float GetElapsedTime() const;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
		float elapsedSeconds;
		bool running;
	};

	struct DelayedCallback {
		float targetSeconds;
		float currentSeconds; 
		std::function<void()> callback;
	};


	SubTimer timer;
	SubTimer timerSinceStartup;

	std::vector<DelayedCallback> delayedCallbacks;

	float elapsedTime = 0.0f;
	float deltaTime = 0.0f;

};
