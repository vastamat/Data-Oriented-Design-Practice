#pragma once

#include "Component.h"
#include "Entity.h"

#include "Containers/ContainerUtils.h"

#include <bitset>
#include <vector>

namespace dode
{
				constexpr uint32 c_NumberOfMaxComponentTypes = 32;
				constexpr uint32 c_NumberOfMaxComponentInstancesOfOneType = 1000;

				using ComponentMask = std::bitset<c_NumberOfMaxComponentTypes>;

				struct EntityComponentMap
				{
								Entity m_EntityComponentbelongsTo;
								uint32 m_ComponentIndexInArray;

								EntityComponentMap( Entity _EntityComponentbelongsTo, uint32 _ComponentIndexInArray )
												: m_EntityComponentbelongsTo( _EntityComponentbelongsTo )
												, m_ComponentIndexInArray( _ComponentIndexInArray )
								{
								}
								
				};

				class ComponentIdInArrayToEntityMapManager
				{
				public:
								void RegisterEntityForComponent( uint32 _ComponentIdInArray, Entity _Entity )
								{
												DENSURE( IsEntityRegistered( _Entity ) == false );
												m_ComponentIdInArrayToEntityMap.emplace_back( _Entity, _ComponentIdInArray );
								}
								void UnregisterEntityForComponent( Entity _Entity )
								{
												for ( size_t i = 0; i < m_ComponentIdInArrayToEntityMap.size(); i++ )
												{
																if ( m_ComponentIdInArrayToEntityMap[i].m_EntityComponentbelongsTo == _Entity )
																{
																				SwapAndPop( m_ComponentIdInArrayToEntityMap, i );
																				return;
																}
												}
								}
								uint32 GetComponentIdInArrayForEntity( Entity _Entity ) const
								{
												int32 index = GetIndexInArrayForEntity( _Entity );

												DENSURE( index != -1 );

												return m_ComponentIdInArrayToEntityMap[index].m_ComponentIndexInArray;
								}

								void ChangeComponentIdForEntity( Entity _Entity, uint32 _NewComponentIndexInArray )
								{
												int32 index = GetIndexInArrayForEntity( _Entity );

												DENSURE( index != -1 );

												m_ComponentIdInArrayToEntityMap[index].m_ComponentIndexInArray = _NewComponentIndexInArray;
								}

								Entity GetEntityThatOwnsComponentAtIndex( uint32 _ComponentIndex )
								{
												for ( size_t i = 0; i < m_ComponentIdInArrayToEntityMap.size(); i++ )
												{
																if ( m_ComponentIdInArrayToEntityMap[i].m_ComponentIndexInArray == _ComponentIndex )
																{
																				return m_ComponentIdInArrayToEntityMap[i].m_EntityComponentbelongsTo;
																}
												}

												DENSURE( false );
												return Entity{ 0 };
								}
				private:
								int32 GetIndexInArrayForEntity( Entity _Entity ) const
								{
												for ( size_t i = 0; i < m_ComponentIdInArrayToEntityMap.size(); i++ )
												{
																if ( m_ComponentIdInArrayToEntityMap[i].m_EntityComponentbelongsTo == _Entity )
																{
																				return i;
																}
												}
												return -1;
								}

								bool IsEntityRegistered( Entity _Entity ) const
								{
												int32 index = GetIndexInArrayForEntity( _Entity );

												return index != -1;
								}

				private:
								std::vector<EntityComponentMap> m_ComponentIdInArrayToEntityMap;
				};

				class BaseComponentManager
				{
				public:
								virtual ~BaseComponentManager() {}

								virtual void RemoveComponent( Entity _EntityComponentBelongsTo ) = 0;
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
												DENSURE( m_NumberOfComponentsActive <= c_NumberOfMaxComponentInstancesOfOneType );
												m_Components[m_NumberOfComponentsActive] = std::move( _Component );
												m_ComponentIdInArrayToEntityMapManager.RegisterEntityForComponent( m_NumberOfComponentsActive, _EntityComponentBelongsTo );
												m_NumberOfComponentsActive++;
								}

								virtual void RemoveComponent( Entity _EntityComponentBelongsTo ) override
								{
												uint32 ComponentIdToRemove = m_ComponentIdInArrayToEntityMapManager.GetComponentIdInArrayForEntity( _EntityComponentBelongsTo );

												Entity EntityThatOwnsComponentAtLastIndex = m_ComponentIdInArrayToEntityMapManager.GetEntityThatOwnsComponentAtIndex( m_NumberOfComponentsActive );

												m_Components[ComponentIdToRemove] = std::move( m_Components[m_NumberOfComponentsActive] );

												m_ComponentIdInArrayToEntityMapManager.ChangeComponentIdForEntity( EntityThatOwnsComponentAtLastIndex, ComponentIdToRemove );

												m_ComponentIdInArrayToEntityMapManager.UnregisterEntityForComponent( _EntityComponentBelongsTo );

												m_NumberOfComponentsActive--;
								}

				private:
								ComponentType m_Components[c_NumberOfMaxComponentInstancesOfOneType];
								ComponentIdInArrayToEntityMapManager m_ComponentIdInArrayToEntityMapManager;
								int32 m_NumberOfComponentsActive;
				};
}
