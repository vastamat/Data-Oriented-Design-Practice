#pragma once

#include <chrono>

namespace dode
{
				using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
				using FloatDurationSeconds = std::chrono::duration<float>;
				using FloatDurationMilli = std::chrono::duration<float, std::milli>;

				class Timer
				{
				public:
								void Start();
								void SleepFor(float _Milli);

								FloatDurationSeconds GetDuration() const;
								float ElapsedSeconds() const;
								float ElapsedMilli() const;

				private:
								TimePoint m_Start;
				};
}
