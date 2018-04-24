#pragma once

#include "EventQueue.h"

namespace dode
{
				namespace EventDispatcher
				{
								template <typename EventType, typename Listener>
								void AddListener( Listener* _Listener )
								{
												EventQueue<EventType>::GetInstance().AddListener( _Listener );
								}

								template <typename EventType, typename Listener>
								void RemoveListener( Listener* _Listener )
								{
												EventQueue<EventType>::GetInstance().RemoveListener( _Listener );
								}

								template <typename EventType>
								void BroadcastEvent( const EventType& _Event )
								{
												EventQueue<EventType>::GetInstance().Broadcast( _Event );
								}
				};
}