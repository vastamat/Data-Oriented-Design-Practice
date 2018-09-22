#pragma once

#include "ComponentManager.h"
#include "Entity.h"

#include <bitset>
#include <queue>

namespace dode
{
				class EntityManager
				{
				public:
								Entity Create();

								inline void RecycleEntity( Entity _Entity )
								{
												DENSURE( _Entity.m_Id < m_EntityKeyMasks.size() );
												m_EntityKeyMasks[_Entity.m_Id].reset();
												m_FreeIndices.emplace( _Entity.m_Id );
								}

								inline const ComponentMask& GetComponentMaskForEntity( Entity _Entity )
								{
												DENSURE( _Entity.m_Id < m_EntityKeyMasks.size() );
												return m_EntityKeyMasks[_Entity.m_Id];
								}

								inline void ActivateComponentBitForEntity( Entity _Entity, uint32 _BitIndex )
								{
												DENSURE( _Entity.m_Id < m_EntityKeyMasks.size() );
												m_EntityKeyMasks[_Entity.m_Id].set( _BitIndex, true );
								}

								inline void DeactivateComponentBitForEntity( Entity _Entity, uint32 _BitIndex )
								{
												DENSURE( _Entity.m_Id < m_EntityKeyMasks.size() );
												m_EntityKeyMasks[_Entity.m_Id].set( _BitIndex, false );
								}
				private:
								std::queue<uint32> m_FreeIndices;
								std::vector<ComponentMask> m_EntityKeyMasks;
				};
}