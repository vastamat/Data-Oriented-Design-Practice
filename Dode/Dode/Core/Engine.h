#pragma once

#include "../Video/Video.h"

namespace dode
{
				class Engine
				{
				public:
								Engine();

								void Run();
								void Stop();

								struct OnExit {};

								void OnEvent(const OnExit & _OnExit);

				private:
								Video m_Video;

								bool m_IsRunning;
				};
}