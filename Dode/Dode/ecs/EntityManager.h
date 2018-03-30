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
																assert(index < (1 << ENTITY_INDEX_BITS));
												}
												return CrateEntity(index, m_Generation[index]);
								}

				private:
								std::vector<uint8_t> m_Generation;
								std::deque<uint32_t> m_FreeIndices;
				};
}