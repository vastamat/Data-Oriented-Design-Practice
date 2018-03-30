#pragma once

#include "Entity.h"

#include <assert.h>
#include <deque>
#include <vector>

constexpr uint32_t MINIMUM_FREE_INDICES = 1024u;

namespace dode
{
				class EntityManager
				{
				public:
								Entity Create()
								{
												uint32_t index = 0u;

												if (m_FreeIndices.size() > MINIMUM_FREE_INDICES)
												{
																index = m_FreeIndices.front();
																m_FreeIndices.pop_front();
												}
												else
												{
																m_Generation.push_back(0u);
																index = m_Generation.size() - 1;
																assert(index < (1u << ENTITY_INDEX_BITS));
												}
												return CrateEntity(index, m_Generation[index]);
								}

								bool IsAlive(Entity _Entity)
								{
												return m_Generation[_Entity.GetId()] == _Entity.GetGeneration();
								}

								void DestroyEntity(Entity _Entity)
								{
												const uint32_t Index = _Entity.GetId();
												++m_Generation[Index];
												m_FreeIndices.push_back(Index);
								}

				private:
								std::vector<uint8_t> m_Generation;
								std::deque<uint32_t> m_FreeIndices;
				};
}