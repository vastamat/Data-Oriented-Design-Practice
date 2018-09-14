#pragma once

#include "Entity.h"
#include "ComponentManager.h"

#include <bitset>
#include <vector>

namespace dode
{
				struct EntityKeyMask
				{
								Entity m_EntityMaskBelongsTo;
								std::bitset<c_NumberOfMaxComponentTypes> m_EntityKeyMask;

								bool operator==( const Entity& _Other )
								{
												return m_EntityMaskBelongsTo == _Other;
								}
				};

				class EntityKeyMaskManager
				{
				public:
								EntityKeyMaskManager();
								~EntityKeyMaskManager();

								std::bitset<c_NumberOfMaxComponentTypes>* GetMaskForEntity( Entity _Entity )
								{
												for ( auto& KeyMask : m_EntityKeyMasks )
												{
																if ( KeyMask.m_EntityMaskBelongsTo == _Entity )
																{
																				return &KeyMask.m_EntityKeyMask;
																}
												}

												return nullptr;
								}

				private:
								std::vector<EntityKeyMask> m_EntityKeyMasks;
				};
}