#include "ThreadPool.h"

namespace dode
{
				ThreadPool::ThreadPool()
								: m_Tasks()
								, m_Threads()
								, m_ConditionToAwake()
								, m_Mutex()
								, m_IsShuttingDown( false )
				{
								auto numberOfSupportedThreadsHint = std::thread::hardware_concurrency();
								m_Threads.reserve( numberOfSupportedThreadsHint );

								for ( size_t i = 0; i <= numberOfSupportedThreadsHint; i++ )
								{
												m_Threads.emplace_back( std::bind( &ThreadPool::TaskRunner, this ) );
								}
				}

				ThreadPool::~ThreadPool()
				{
								{
												std::lock_guard<std::mutex> lock{ m_Mutex };
												m_IsShuttingDown = true;
								}

								m_ConditionToAwake.notify_all();

								for ( auto& thread : m_Threads )
								{
												thread.join();
								}
				}

				void ThreadPool::TaskRunner()
				{
								while ( true )
								{
												Task task = []() {};

												{
																std::unique_lock<std::mutex> lock{ m_Mutex };

																m_ConditionToAwake.wait( lock, [ = ] { return m_IsShuttingDown || !m_Tasks.empty(); } );

																if ( m_IsShuttingDown && m_Tasks.empty() )
																{
																				break;
																}

																task = std::move( m_Tasks.front() );
																m_Tasks.pop();
												}

												task();
								}
				}
}