#pragma once

#include "Core/CommonIncludes.h"

namespace dode
{
				/*constexpr uint32 ENTITY_INDEX_BITS = 22u;
				constexpr uint32 ENTITY_INDEX_MASK = ( 1u << ENTITY_INDEX_BITS ) - 1u;

				constexpr uint32 ENTITY_GENERATION_BITS = 8u;
				constexpr uint32 ENTITY_GENERATION_MASK = ( 1u << ENTITY_GENERATION_BITS ) - 1u;

				struct Entity
				{
								uint32 Id = 0u;

								inline uint32 GetId() const { return Id & ENTITY_INDEX_MASK; }
								inline uint32 GetGeneration() const { return ( Id >> ENTITY_INDEX_BITS ) & ENTITY_GENERATION_MASK; }

								inline bool IsNull() const { return Id == 0u; }

								inline bool operator==( const Entity& _Rhs ) const { return Id == _Rhs.Id; }
								inline bool operator!=( const Entity& _Rhs ) const { return Id != _Rhs.Id; }
				};

				inline Entity CrateEntity( uint32 _Id, uint8 _Generation )
				{
								uint32 Generation32 = static_cast< uint32 >( _Generation );
								return { ( Generation32 << ENTITY_INDEX_BITS ) | _Id };
				}*/

				constexpr uint32 c_MaxEntities = ( 1 << 24 ) - 1;

				struct EntityID
				{
								uint32 m_Index : 24;
								uint32 m_Version : 8;
				};
				static_assert( sizeof( EntityID ) == 4, "Entity ID must be 4 bytes" );

				struct Entity
				{
								EntityID m_EntityID;

								inline	uint32 Index() const { return m_EntityID.m_Index; }
								inline	uint8 Version() const { return m_EntityID.m_Version; }

								inline bool IsNull() const { return m_EntityID.m_Index == 0u; }
								inline bool IsValid() const { return m_EntityID.m_Index > 0 && m_EntityID.m_Index < c_MaxEntities; }

								inline bool operator==( const Entity& _Rhs ) const { return m_EntityID.m_Index == _Rhs.m_EntityID.m_Index; }
								inline bool operator!=( const Entity& _Rhs ) const { return m_EntityID.m_Index != _Rhs.m_EntityID.m_Index; }
				};

				inline Entity CrateEntity( uint32 _Index, uint8 _Version )
				{
								EntityID newEntityId{ _Index, _Version };
								return Entity{ newEntityId };
				}
}
