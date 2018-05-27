#include "Engine.h"

#include "../EventSystem/EventDispatcher.h"

namespace dode
{
				Engine::Engine()
								: m_Video()
								, m_IsRunning( true )
				{
								EventDispatcher::AddListener<OnExit>( this );
				}

				void Engine::Run()
				{
								m_Video.Initialize( 1280, 720, false, false );

								while ( m_IsRunning )
								{
												m_Video.PollEvents();

												m_Video.SwapBuffers();
								}

								m_Video.Shutdown();

								EventDispatcher::RemoveListener<OnExit>( this );
				}

				void Engine::Stop()
				{
								m_IsRunning = false;
				}
				void Engine::OnEvent( const OnExit & _OnExit )
				{
								m_IsRunning = false;
				}
}
