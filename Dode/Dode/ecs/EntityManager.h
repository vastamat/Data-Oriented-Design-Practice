#pragma once

#include "Entity.h"

#include <deque>
#include <vector>

namespace dode
{
				constexpr uint32 MINIMUM_FREE_INDICES = 1024u;

				class EntityManager
				{
				public:
								Entity Create()
								{
												uint32 index = 0u;

												if ( m_FreeIndices.size() > MINIMUM_FREE_INDICES )
												{
																index = m_FreeIndices.front();
																m_FreeIndices.pop_front();
												}
												else
												{
																m_Generation.push_back( 0u );
																index = m_Generation.size() - 1;
																DENSURE( index < ( 1u << ENTITY_INDEX_BITS ) );
												}
												return CrateEntity( index, m_Generation[index] );
								}

								inline bool IsAlive( Entity _Entity )
								{
												return m_Generation[_Entity.GetId()] == _Entity.GetGeneration();
								}

								inline void DestroyEntity( Entity _Entity )
								{
												const uint32 Index = _Entity.GetId();
												++m_Generation[Index];
												m_FreeIndices.push_back( Index );
								}

				private:
								std::vector<uint8> m_Generation;
								std::deque<uint32> m_FreeIndices;
				};
}