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
								World();
								~World();

								Entity CreateEntity();
								void DestroyEntity( Entity _Entity );

								template<typename ComponentType>
								void AddComponent( Entity _E, ComponentType _Data );
								template<typename ComponentType>
								void RemoveComponent( Entity _E );
								// template<typename ComponentType, typename Args...>
								// void UnpackComponentData(Entity _E, ComponentHandle<ComponentType>& _ComponentHandle, ComponentHandle<Args>& ..._OtherComponents)

								void AddSystem( std::unique_ptr<System> _System );
								void RemoveSystem( System* _System );

				private:
								template<typename ComponentType>
								ComponentManager<ComponentType>* GetPtrToDerivedComponentManager();

				private:
								EntityManager m_EntityManager;
								std::array<std::unique_ptr<BaseComponentManager>, c_NumberOfMaxComponentTypes> m_ComponentManagers;
								std::vector<std::unique_ptr<System>> m_Systems;
				};

				template<typename ComponentType>
				inline void World::AddComponent( Entity _E, ComponentType _Data )
				{
								ComponentManager<ComponentType>* derivedComponentManager = GetPtrToDerivedComponentManager<ComponentType>();

								derivedComponentManager->AddComponent( _E, _Data );

								//Remove Entity From Systems it's currently registered
								// auto CurrentKeyMask = MaskManager.GetMaskForEntity(_E);
								// if CurrentKeyMask != null
								// Get Systems With Current Key Mask
								// Remove Entity E from them
								//Add Entity to Systems which correspond to the new component mask
								
				}
				template<typename ComponentType>
				inline void World::RemoveComponent( Entity _E )
				{
								ComponentManager<ComponentType>* derivedComponentManager = GetPtrToDerivedComponentManager<ComponentType>();

								derivedComponentManager->RemoveComponent( _E );

								//Remove Entity From Systems it's currently registered

								//Add Entity to Systems which correspond to the new component mask
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