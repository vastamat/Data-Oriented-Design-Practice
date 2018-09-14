#pragma once

#include "Component.h"
#include "Entity.h"

#include <map>

namespace dode
{
				constexpr uint32 c_NumberOfMaxComponentTypes = 32;
				constexpr uint32 c_NumberOfMaxComponentInstancesOfOneType = 1000;

				struct EntityIdToComponentInstanceMap
				{
								uint32 m_EntityId;
								uint32 m_ComponentIndexInArray;
				};

				class BaseComponentManager
				{
				public:
								virtual ~BaseComponentManager() {}
				};

				template<typename ComponentType>
				class ComponentManager : public BaseComponentManager
				{
								static_assert( std::is_base_of<Component, ComponentType>::value, "Must inherit from Component" );
								static_assert( std::is_standard_layout<ComponentType>::value, "Must have standard layout (all public, no virtual functions)" );

				public:
								ComponentManager()
												: m_NumberOfComponentsActive( 0 )
								{
								}
								~ComponentManager()
								{
								}
								void AddComponent( Entity _EntityComponentBelongsTo, ComponentType _Component )
								{
												assert( m_NumberOfComponentsActive <= c_NumberOfMaxComponentInstancesOfOneType );
												m_Components[m_NumberOfComponentsActive] = std::move( _Component );
												m_EntityIdToComponentIdInArrayMap[_EntityComponentBelongsTo] = m_NumberOfComponentsActive;
												m_NumberOfComponentsActive++;
								}

								void RemoveComponent( Entity _EntityComponentBelongsTo )
								{
												uint32 ComponentIndexInArray = m_EntityIdToComponentIdInArrayMap[_EntityComponentBelongsTo];
												m_Components[ComponentIndexInArray] = std::move( m_Components[--m_NumberOfComponentsActive] );
								}

				private:
								std::map<Entity, uint32> m_EntityIdToComponentIdInArrayMap;
								ComponentType m_Components[c_NumberOfMaxComponentInstancesOfOneType];
								int32 m_NumberOfComponentsActive;
				};
}
