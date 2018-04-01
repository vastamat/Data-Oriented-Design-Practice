#pragma once

#include "../Core/CommonIncludes.h"

namespace dode
{
				constexpr uint32 ENTITY_INDEX_BITS = 22u;
				constexpr uint32 ENTITY_INDEX_MASK = (1u << ENTITY_INDEX_BITS) - 1u;

				constexpr uint32 ENTITY_GENERATION_BITS = 8u;
				constexpr uint32 ENTITY_GENERATION_MASK = (1u << ENTITY_GENERATION_BITS) - 1u;

				struct Entity
				{
								uint32 Id = 0u;

								uint32 GetId() const { return Id & ENTITY_INDEX_MASK; }
								uint32 GetGeneration() const { return (Id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }

								bool IsNull() const { return Id == 0u; }

								bool operator==(const Entity& _Rhs) const { return Id == _Rhs.Id; }
								bool operator!=(const Entity& _Rhs) const { return Id != _Rhs.Id; }
				};

				inline Entity CrateEntity(uint32 _Id, uint8 _Generation)
				{
								uint32 Generation32 = static_cast<uint32>(_Generation);
								return { (Generation32 << ENTITY_INDEX_BITS) | _Id };
				}
}
