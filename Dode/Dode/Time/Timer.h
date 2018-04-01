#pragma once

#include <chrono>
#include <thread>

namespace dode
{
				using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
				using FloatDurationSeconds = std::chrono::duration<float>;
				using FloatDurationMilli = std::chrono::duration<float, std::milli>;

				class Timer
				{
				public:
								inline void Start()
								{
												m_Start = TimePoint::clock::now();
								}

								inline void SleepFor(float _Milli)
								{
												std::this_thread::sleep_for(FloatDurationMilli(_Milli));
								}

								inline FloatDurationSeconds GetDuration() const
								{
												return TimePoint::clock::now() - m_Start;
								}

								inline float ElapsedSeconds() const
								{
												return GetDuration().count();
								}

								inline float ElapsedMilli() const
								{
												return std::chrono::duration_cast<FloatDurationMilli>(GetDuration()).count();
								}

				private:
								TimePoint m_Start;
				};
}
