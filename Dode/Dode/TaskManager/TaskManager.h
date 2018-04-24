#pragma once

#include "Task.h"
#include "../Containers/ConcurrentQueue.h"

#include <algorithm>
#include <list>

namespace dode
{
				class TaskManager
				{
				public:
								using TaskPtr = std::shared_ptr<Task>;
								using TaskQueue = ConcurrentQueue<TaskPtr>;

								struct StopEvent {};

								TaskManager();
								TaskManager( uint8 _NumThreads );
								~TaskManager();

								void Add( TaskPtr _Task );

								void Start();
								void Stop();

								void OnEvent( const StopEvent& _StopEvent );
								void OnEvent( const Task::TaskCompleted& _TaskCompleted );

				private:
								void Worker();
								void Execute( TaskPtr _Task );
								void Synchronize();

				private:
								std::vector<std::thread> m_Threads;
								uint8 m_NumThreads;
								bool m_Running;

								TaskQueue m_TaskQueue[2];
								TaskQueue m_BackgroundTasks;
								TaskQueue m_SyncTasks;

								uint8 m_ReadList;
								uint8 m_WriteList;

								using Mutex = std::mutex;
								using ConditionVariable = std::condition_variable;

								mutable Mutex m_SyncMutex;
								ConditionVariable m_Condition;
								uint8 m_NumTasksToWaitFor;
				};
}