#include "Timer.h"

#include <thread>

namespace dode
{
				void Timer::Start()
				{
								m_Start = TimePoint::clock::now();
				}

				void Timer::SleepFor(float _Milli)
				{
								std::this_thread::sleep_for(FloatDurationMilli(_Milli));
				}

				FloatDurationSeconds Timer::GetDuration() const
				{
								return TimePoint::clock::now() - m_Start;
				}

				float Timer::ElapsedSeconds() const
				{
								return GetDuration().count();
				}

				float Timer::ElapsedMilli() const
				{
								return std::chrono::duration_cast<FloatDurationMilli>(GetDuration()).count();
				}
}