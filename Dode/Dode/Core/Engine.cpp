#include "Engine.h"

#include <algorithm>

namespace dode
{
				Engine::Engine()
								: m_Video()
								, m_ThreadPool()
								, m_IsRunning( true )
				{
				}

				void Engine::SetApplication( std::unique_ptr<Application> _Application )
				{
								m_Application = std::move( _Application );
				}

				void Engine::Run()
				{
								InitializeEngineSubSystems();

								while ( m_IsRunning )
								{
												if ( m_Application )
												{

												}
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
								m_Video.Initialize( 1080, 760, false, false );
				}

				void Engine::ShutdownEngineSubSystems()
				{
								m_Video.Shutdown();
				}
}
