#include "Application.h"

namespace dode
{
				Application::Application()
								: m_Worlds()
								, m_CurrentWorldId( -1 )
								, m_NextWorldId( -1 )
								, m_State( ApplicationState::NotRunning )
				{
				}

				Application::~Application()
				{
				}

				Application::Application( Application && _Other ) noexcept
								: m_Worlds( std::move( _Other.m_Worlds ) )
								, m_CurrentWorldId( std::move( _Other.m_CurrentWorldId ) )
								, m_NextWorldId( std::move( _Other.m_NextWorldId ) )
								, m_State( std::move( _Other.m_State ) )
				{
				}

				Application & Application::operator=( Application && _Other ) noexcept
				{
								m_Worlds = std::move( _Other.m_Worlds );
								m_CurrentWorldId = std::move( _Other.m_CurrentWorldId );
								m_NextWorldId = std::move( _Other.m_NextWorldId );
								m_State = std::move( _Other.m_State );

								return *this;
				}

				World& Application::CreateNewWorld( const std::string & _WorldName )
				{
								m_Worlds.emplace_back( _WorldName );
								return m_Worlds.back();
				}

				void Application::SetReadyToBeginRunning()
				{
								m_CurrentWorldId = 0;
								m_State = ApplicationState::Startup;
				}

				void Application::Update()
				{
								switch ( m_State )
								{
												case dode::ApplicationState::NotRunning:	break;

												case dode::ApplicationState::Startup:
												{
																m_Worlds[m_CurrentWorldId].OnEnter();
																m_State = ApplicationState::Running;
																break;
												}

												case dode::ApplicationState::Running:
												{
																m_Worlds[m_CurrentWorldId].UpdateSystems( 1.0f / 60.0f );
																break;
												}

												case dode::ApplicationState::Transitioning:
												{
																DENSURE( m_NextWorldId != -1 );
																m_Worlds[m_CurrentWorldId].OnExit();
																m_Worlds[m_NextWorldId].OnEnter();
																m_CurrentWorldId = m_NextWorldId;
																m_NextWorldId = -1;
																m_State = ApplicationState::Running;
																break;
												}
																
												case dode::ApplicationState::Exitting:
												{
																m_State = ApplicationState::NotRunning;
																break;
												}

												default:	break;
								}
				}

				void Application::BeginTransitionToWorld( std::string & _WorldName )
				{
								for ( size_t i = 0; i < m_Worlds.size(); i++ )
								{
												if ( m_Worlds[i].GetIdName() == _WorldName )
												{
																m_NextWorldId = i;
																m_State = ApplicationState::Transitioning;
																return;
												}
								}
				}
}

