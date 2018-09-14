#pragma once

#include <condition_variable>
#include <functional>
#include <iostream>
#include <future>
#include <vector>
#include <thread>
#include <queue>

namespace dode
{
				class ThreadPool
				{
				public:
								ThreadPool();
								~ThreadPool();

								template<typename T>
								auto Enqueue( T _Task ) -> std::future<decltype( _Task() )>
								{
												using ReturnType = decltype( _Task() );
												auto wrapper = std::make_shared<std::packaged_task<ReturnType()>>( std::move( _Task ) );
												{
																{
																				std::lock_guard<std::mutex> lock( m_Mutex );

																				m_Tasks.emplace( [ wrapper ]()
																				{
																								( *wrapper )( );
																				} );
																}

																m_ConditionToAwake.notify_one();
																return wrapper->get_future();
												}
								}

				private:
								void TaskRunner();

				private:
								using Task = std::function<void()>;

								std::queue<Task> m_Tasks;
								std::vector<std::thread> m_Threads;
								std::condition_variable m_ConditionToAwake;
								std::mutex m_Mutex;
								bool m_IsShuttingDown;
				};
}
