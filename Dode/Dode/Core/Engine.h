#pragma once

#include "CommonIncludes.h"

#include "App/Application.h"
#include "Video/Video.h"
#include "TaskManager/ThreadPool.h"

#include <vector>
#include <memory>

namespace dode
{
				class Engine
				{
				public:
								Engine();

								void SetApplication( Application&& _Application );
								void Run();
								void Stop();

				private:
								void InitializeEngineSubSystems();
								void ShutdownEngineSubSystems();

				private:
								Application m_Application;
								Video m_Video;
								ThreadPool m_ThreadPool;

								bool m_IsRunning;
				};
}