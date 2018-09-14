#pragma once

#include "Core/CommonIncludes.h"

#include <memory>

namespace dode
{
				class Task
				{
				public:
								using TaskPtr = std::shared_ptr<Task>;

								struct TaskBeginning
								{
												TaskPtr m_Task;
								};

								struct TaskCompleted
								{
												TaskPtr m_Task;
								};

								enum Type
								{
												None = 0,
												Repeating = 1 << 0,
												ThreadSafe = 1 << 1,
												FrameSync = 1 << 2,

												SingleThreaded = None,
												SingleThreadedRepeating = Repeating,
												Background = ThreadSafe,
												BackgroundRepeating = ThreadSafe | Repeating,
												BackgroundSync = ThreadSafe | FrameSync,
												BackgroundSyncRepeating = ThreadSafe | Repeating | FrameSync,

												All = ~0x0
								};

								Task( uint8 _TaskFlags )
												: m_TaskFlags( _TaskFlags )
								{
								}
								virtual ~Task() {}

								virtual void Run() = 0;

								void StopRepeating() { m_TaskFlags &= ~Repeating; }

				protected:
								friend class TaskManager;

								inline uint8 GetTaskFlags() const { return m_TaskFlags; }

				private:
								uint8 m_TaskFlags;
				};
}
