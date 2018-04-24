#pragma once

#include <queue>
#include <thread>
#include <mutex>

namespace dode
{
				template<typename T>
				class ConcurrentQueue
				{
								using Queue = std::queue<T>;
								using Mutex = std::mutex;
								using ScopedLock = std::unique_lock<Mutex>;
								using ConditionVariable = std::condition_variable;

				public:
								bool Empty() const
								{
												ScopedLock( m_Mutex );
												return m_Queue.empty();
								}
								void Push( const T& _Value )
								{
												{
																ScopedLock( m_Mutex );
																m_Queue.push( _Value );
												}
												m_Condition.notify_one();
								}
								bool TryPop( T& _Result )
								{
												ScopedLock lock( m_Mutex );

												if ( m_Queue.empty() )
												{
																return false;
												}

												_Result = m_Queue.front();
												m_Queue.pop();

												return true;
								}
								T WaitPop()
								{
												ScopedLock lock( m_Mutex );

												while ( m_Queue.empty() )
												{
																m_Condition.wait( lock );
												}

												T result( m_Queue.front() );
												m_Queue.pop();

												return result;
								}
								std::size_t Size() const
								{
												ScopedLock( m_Mutex );
												return m_Queue.size();
								}

				private:
								Queue m_Queue;
								mutable Mutex m_Mutex;
								ConditionVariable m_Condition;
				};
}
