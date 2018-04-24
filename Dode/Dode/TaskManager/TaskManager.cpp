#include "TaskManager.h"

#include "../EventSystem/EventDispatcher.h"

namespace dode
{
				TaskManager::TaskManager()
								: m_NumThreads( std::thread::hardware_concurrency() + 1 )
								, m_ReadList( 1u )
								, m_WriteList( 0u )
								, m_NumTasksToWaitFor( 0u )
								, m_Running( false )
				{
				}

				TaskManager::TaskManager( uint8 _NumThreads )
								: m_NumThreads( _NumThreads )
								, m_ReadList( 1u )
								, m_WriteList( 0u )
								, m_NumTasksToWaitFor( 0u )
								, m_Running( false )
				{
				}

				TaskManager::~TaskManager()
				{
								for ( auto& it : m_Threads )
								{
												it.join();
								}
				}

				void TaskManager::Add( TaskPtr _Task )
				{
								uint8 flags = _Task->GetTaskFlags();

								if ( flags & Task::ThreadSafe )
								{
												if ( flags & Task::FrameSync )
												{
																m_SyncTasks.Push( _Task );
												}
												else
												{
																m_BackgroundTasks.Push( _Task );
												}
								}
								else
								{
												m_TaskQueue[m_WriteList].Push( _Task );
								}
				}

				void TaskManager::Start()
				{
								m_Running = true;

								EventDispatcher::AddListener<Task::TaskCompleted>( this );
								EventDispatcher::AddListener<StopEvent>( this );

								for ( uint8 i = 0; i < m_NumThreads; i++ )
								{
												m_Threads.emplace_back( std::bind( &TaskManager::Worker, this ) );
								}

								while ( m_Running )
								{
												if ( !m_TaskQueue[m_ReadList].Empty() )
												{
																TaskPtr task = m_TaskQueue->WaitPop();
																Execute( task );
												}
												else
												{
																Synchronize();
																std::swap( m_ReadList, m_WriteList );
												}

												std::this_thread::yield();
								}
				}
				void TaskManager::Stop()
				{
								m_Running = false;
				}

				void TaskManager::OnEvent( const StopEvent & _StopEvent )
				{
								Stop();
				}

				void TaskManager::OnEvent( const Task::TaskCompleted & _TaskCompleted )
				{
								if ( _TaskCompleted.m_Task->GetTaskFlags() & Task::Type::Repeating )
								{
												Add( _TaskCompleted.m_Task );
								}
				}

				void TaskManager::Worker()
				{
								TaskPtr task;

								while ( m_Running )
								{
												bool exec = m_BackgroundTasks.TryPop( task );

												if ( exec )
												{
																Execute( task );

																if ( task->GetTaskFlags() & Task::FrameSync )
																{
																				{
																								std::lock_guard<Mutex> lock( m_SyncMutex );
																								m_NumTasksToWaitFor--;
																				}
																				m_Condition.notify_one();
																}
																std::this_thread::yield();
												}
												else
												{
																std::this_thread::sleep_for( std::chrono::microseconds( 1667 ) );
												}
								}
				}

				void TaskManager::Execute( TaskPtr _Task )
				{
								EventDispatcher::BroadcastEvent( Task::TaskBeginning{ _Task } );
								_Task->Run();
								EventDispatcher::BroadcastEvent( Task::TaskCompleted{ _Task } );
				}

				void TaskManager::Synchronize()
				{
								std::unique_lock<Mutex> lock( m_SyncMutex );

								while ( m_NumTasksToWaitFor > 0 )
								{
												m_Condition.wait( lock );
								}

								m_NumTasksToWaitFor = static_cast< uint8 >( m_SyncTasks.Size() );

								while ( !m_SyncTasks.Empty() )
								{
												m_BackgroundTasks.Push( m_SyncTasks.WaitPop() );
								}
				}
}