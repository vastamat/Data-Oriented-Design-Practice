#pragma once

#include "Entity.h"
#include "ComponentManager.h"

#include <bitset>
#include <vector>

namespace dode
{
				class World;

				class System
				{
				public:
								System(const std::string& _SystemName);
								virtual ~System();

								virtual void Update( const World& _World, float _Dt ) = 0;

								void RegisterEntity( Entity _Entity );
								void UnregisterEntity( Entity _Entity );

								inline const std::string& GetName() const noexcept { return m_SystemName; }

				protected:
								std::vector<Entity> m_RegisteredEntities;
								std::bitset<c_NumberOfMaxComponentTypes> m_SystemSignature;
								std::string m_SystemName;
				};
}
