#pragma once

#include <cstdint>

namespace dode
{
				constexpr uint32_t ENTITY_INDEX_BITS = 22u;
				constexpr uint32_t ENTITY_INDEX_MASK = (1u << ENTITY_INDEX_BITS) - 1u;

				constexpr uint32_t ENTITY_GENERATION_BITS = 8u;
				constexpr uint32_t ENTITY_GENERATION_MASK = (1u << ENTITY_GENERATION_BITS) - 1u;

				struct Entity
				{
								uint32_t Id = 0u;

								uint32_t GetId() const { return Id & ENTITY_INDEX_MASK; }
								uint32_t GetGeneration() const { return (Id >> ENTITY_INDEX_BITS) & ENTITY_GENERATION_MASK; }

								bool IsNull() const { return Id == 0u; }

								bool operator==(const Entity& _Rhs) const { return Id == _Rhs.Id; }
								bool operator!=(const Entity& _Rhs) const { return Id != _Rhs.Id; }
				};

				inline Entity CrateEntity(uint32_t _Id, uint8_t _Generation)
				{
								uint32_t Generation32 = static_cast<uint32_t>(_Generation);
								return { (Generation32 << ENTITY_INDEX_BITS) | _Id };
				}
}