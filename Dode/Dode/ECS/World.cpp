#include "World.h"

namespace dode
{
				World::World( const std::string& _IdentificationName )
								: m_IdentificationName(_IdentificationName)
				{
				}
				World::~World()
				{
				}

				World::World( World && _Other ) noexcept
								: m_EntityManager(std::move(_Other.m_EntityManager))
								, m_ComponentManagers( std::move( _Other.m_ComponentManagers ) )
								, m_Systems( std::move( _Other.m_Systems ) )
								, m_IdentificationName( std::move( _Other.m_IdentificationName ) )
				{
				}

				World & World::operator=( World && _Other ) noexcept
				{
								m_EntityManager = std::move( _Other.m_EntityManager );
								m_ComponentManagers = std::move( _Other.m_ComponentManagers );
								m_Systems = std::move( _Other.m_Systems );
								m_IdentificationName = std::move( _Other.m_IdentificationName );
								return *this;
				}

				void World::OnEnter()
				{
								for ( auto& system : m_Systems )
								{
												system->Initialize();
								}
				}

				void World::OnExit()
				{
								for ( auto& system : m_Systems )
								{
												system->Uninitialize();
								}
				}

				void World::UpdateSystems( float _DeltaTime )
				{
								for ( auto& system : m_Systems )
								{
												system->Update( *this, _DeltaTime );
								}
				}

				Entity World::CreateEntity()
				{
								return m_EntityManager.Create();
				}

				void World::DestroyEntity( Entity _Entity )
				{
								//Remove Entity from Systems
								for ( auto& System : m_Systems )
								{
												System->UnregisterEntity( _Entity );
								}
								//Remove Entity Components from managers
								
								const ComponentMask& componentMask = m_EntityManager.GetComponentMaskForEntity( _Entity );

								for ( size_t componentTypeId = 0; componentTypeId < componentMask.size(); componentTypeId++ )
								{
												if ( componentMask[componentTypeId] )
												{
																auto& baseComponentManager = m_ComponentManagers[componentTypeId];
																baseComponentManager->RemoveComponent( _Entity );
												}
								}

								m_EntityManager.RecycleEntity( _Entity );
				}

				void World::AddSystem( std::unique_ptr<System> _System )
				{
								m_Systems.emplace_back( std::move( _System ) );
				}
				
				void World::UpdateEntityInSystems( Entity _Entity, const ComponentMask & oldComponentMask, const ComponentMask & newComponentMask )
				{
								for ( auto& System : m_Systems )
								{
												const ComponentMask& systemSignature = System->GetSystemSignature();

												if ( systemSignature == oldComponentMask )
												{
																System->UnregisterEntity( _Entity );
												}
												else if ( systemSignature == newComponentMask )
												{
																System->RegisterEntity( _Entity );
												}
								}
				}
}
