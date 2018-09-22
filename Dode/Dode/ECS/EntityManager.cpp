#include "EntityManager.h"

namespace dode
{
				Entity EntityManager::Create()
				{
								uint32 index = 0u;

								if ( !m_FreeIndices.empty() )
								{
												index = m_FreeIndices.front();
												m_FreeIndices.pop();
								}
								else
								{
												index = m_EntityKeyMasks.size();
												m_EntityKeyMasks.emplace_back();
								}
								return Entity{ index };
				}
}

