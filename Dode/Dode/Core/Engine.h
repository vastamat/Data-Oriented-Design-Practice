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

								void SetApplication( std::unique_ptr<Application> _Application );
								void Run();
								void Stop();

				private:
								void InitializeEngineSubSystems();
								void ShutdownEngineSubSystems();

				private:
								Video m_Video;
								ThreadPool m_ThreadPool;

								std::unique_ptr<Application> m_Application;
								bool m_IsRunning;
				};
}