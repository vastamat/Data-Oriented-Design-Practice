#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "System.h"

#include <array>
#include <memory>

namespace dode
{
				class World
				{
				public:
								World(const std::string& _IdentificationName );
								~World();

								World( const World& _Other ) = delete;
								World& operator=( const World& _Other ) = delete;

								World( World&& _Other ) noexcept;
								World& operator=( World&& _Other ) noexcept;

								void OnEnter();
								void OnExit();

								void UpdateSystems(float _DeltaTime);

								Entity CreateEntity();
								void DestroyEntity( Entity _Entity );

								template<typename ComponentType>
								void AddComponent( Entity _E, ComponentType _Data );
								template<typename ComponentType>
								void RemoveComponent( Entity _E );
								// template<typename ComponentType, typename Args...>
								// void UnpackComponentData(Entity _E, ComponentHandle<ComponentType>& _ComponentHandle, ComponentHandle<Args>& ..._OtherComponents)

								void AddSystem( std::unique_ptr<System> _System );

								inline const std::string& GetIdName() const noexcept { return m_IdentificationName; }

				private:
								template<typename ComponentType>
								ComponentManager<ComponentType>* GetPtrToDerivedComponentManager();

								void UpdateEntityInSystems( Entity _Entity, const ComponentMask& oldComponentMask, const ComponentMask& newComponentMask );

				private:
								EntityManager m_EntityManager;
								std::array<std::unique_ptr<BaseComponentManager>, c_NumberOfMaxComponentTypes> m_ComponentManagers;
								std::vector<std::unique_ptr<System>> m_Systems;
								std::string m_IdentificationName;
				};

				template<typename ComponentType>
				inline void World::AddComponent( Entity _E, ComponentType _Data )
				{
								ComponentManager<ComponentType>* derivedComponentManager = GetPtrToDerivedComponentManager<ComponentType>();

								derivedComponentManager->AddComponent( _E, _Data );

								ComponentMask oldComponentMask = m_EntityManager.GetComponentMaskForEntity( _E );

								m_EntityManager.ActivateComponentBitForEntity( _E, GetIdOfComponentType<ComponentType>() );

								const ComponentMask& newComponentMask = m_EntityManager.GetComponentMaskForEntity( _E );

								UpdateEntityInSystems( _E, oldComponentMask, newComponentMask );
				}
				template<typename ComponentType>
				inline void World::RemoveComponent( Entity _E )
				{
								ComponentManager<ComponentType>* derivedComponentManager = GetPtrToDerivedComponentManager<ComponentType>();

								derivedComponentManager->RemoveComponent( _E );

								ComponentMask oldComponentMask = m_EntityManager.GetComponentMaskForEntity( _E );

								m_EntityManager.DeactivateComponentBitForEntity( _E, GetIdOfComponentType<ComponentType>() );

								const ComponentMask& newComponentMask = m_EntityManager.GetComponentMaskForEntity( _E );

								UpdateEntityInSystems( _E, oldComponentMask, newComponentMask );
				}

				template<typename ComponentType>
				inline ComponentManager<ComponentType>* World::GetPtrToDerivedComponentManager()
				{
								uint32 componentTypeId = GetIdOfComponentType<ComponentType>();
								auto& baseComponentManager = m_ComponentManagers[componentTypeId];
								if ( baseComponentManager == nullptr )
								{
												baseComponentManager = std::make_unique<ComponentManager<ComponentType>>();
								}
								return static_cast< ComponentManager<ComponentType>* >( baseComponentManager.get() );
				}
}