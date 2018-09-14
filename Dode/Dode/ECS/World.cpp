#include "World.h"

namespace dode
{
				World::World()
				{
				}
				World::~World()
				{
				}
				Entity World::CreateEntity()
				{
								return m_EntityManager.Create();
				}
				void World::DestroyEntity( Entity _Entity )
				{
								m_EntityManager.DestroyEntity( _Entity );

								//Remove Entity from Systems
				}
				void World::AddSystem( std::unique_ptr<System> _System )
				{
								m_Systems.emplace_back( std::move( _System ) );
				}
				void World::RemoveSystem( System* _System )
				{
								for ( size_t i = 0; i < m_Systems.size(); i++ )
								{
												if ( m_Systems[i]->GetName() == _System->GetName() )
												{
																m_Systems.erase( m_Systems.begin() + i );
												}
								}
				}
}
