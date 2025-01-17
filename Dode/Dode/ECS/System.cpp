#include "System.h"

#include "Containers/ContainerUtils.h"

namespace dode
{
				System::System()
				{
				}
				System::~System()
				{
				}

				void System::RegisterEntity( Entity _Entity )
				{
								m_RegisteredEntities.push_back( _Entity );
				}

				void System::UnregisterEntity( Entity _Entity )
				{
								for ( uint32 i = 0; i < m_RegisteredEntities.size(); i++ )
								{
												if ( m_RegisteredEntities[i] == _Entity )
												{
																SwapAndPop( m_RegisteredEntities, i );
																return;
												}
								}
				}
}
