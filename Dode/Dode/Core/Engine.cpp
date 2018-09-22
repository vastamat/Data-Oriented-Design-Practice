#include "Engine.h"

#include <algorithm>

namespace dode
{
				Engine::Engine()
								: m_Application()
								, m_Video()
								, m_ThreadPool()
								, m_IsRunning( true )
				{
				}

				void Engine::SetApplication( Application&& _Application )
				{
								m_Application = std::move( _Application );
								m_Application.SetReadyToBeginRunning();
				}

				void Engine::Run()
				{
								InitializeEngineSubSystems();

								while ( m_IsRunning )
								{
												m_Application.Update();
												m_Video.SwapBuffers();
								}

								ShutdownEngineSubSystems();
				}

				void Engine::Stop()
				{
								m_IsRunning = false;
				}

				void Engine::InitializeEngineSubSystems()
				{
								m_Video.Initialize();
				}

				void Engine::ShutdownEngineSubSystems()
				{
								m_Video.Shutdown();
				}
}
