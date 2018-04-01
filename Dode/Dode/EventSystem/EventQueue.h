#pragma once

#include "../Core/CommonIncludes.h"

#include <vector>
#include <mutex>

namespace dode
{
				template <typename EventType>
				class EventQueue
				{
								using OnEventFunc = std::function<void(const EventType&)>;
								using Mutex = std::mutex;
								using ScopedLock = std::lock_guard<Mutex>;

								EventQueue() = default;

				public:
								static EventQueue& GetInstance()
								{
												static EventQueue instance;
												return instance;
								}

								template <typename Listener>
								void AddListener(Listener* _Listener)
								{
												ScopedLock lock(m_Mutex);

												m_Handlers.push_back([_Listener](const EventType& _Event) { _Listener->OnEvent(_Event); });
												m_OriginalPointers.push_back(_Listener);

												DENSURE(m_Handlers.size() == m_OriginalPointers.size());
								}

								template <typename Listener>
								void RemoveListener(Listener* _Listener)
								{
												ScopedLock lock(m_Mutex);

												auto it = std::find(m_OriginalPointers.begin(), m_OriginalPointers.end(), _Listener);

												const bool foundIterator = it != m_OriginalPointers.end();

												DENSURE(foundIterator);

												if (foundIterator)
												{
																auto index = it - m_OriginalPointers.begin();

																m_Handlers.erase(m_Handlers.begin() + index);
																m_OriginalPointers.erase(it);
												}
								}

								void Broadcast(const EventType& _Event)
								{
												/* create a local copy of the OnEvent callbacks,
												 because it is possible for a callback to unregister itself in the event and invalidate the iterator */
												std::vector<OnEventFunc> localQueue(m_Handlers.size());

												{
																ScopedLock lock(m_Mutex);
																localQueue = m_Handlers;
												}

												for (auto& callback : localQueue)
												{
																callback(_Event);
												}
								}

				private:
								std::vector<OnEventFunc> m_Handlers;
								std::vector<void*> m_OriginalPointers;
								Mutex m_Mutex;
				};
}