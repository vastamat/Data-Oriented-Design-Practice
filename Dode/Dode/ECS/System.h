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
								System();
								virtual ~System();

								virtual void Initialize() = 0;
								virtual void Uninitialize() = 0;
								virtual void Update( World& _World, float _Dt ) = 0;

								void RegisterEntity( Entity _Entity );
								void UnregisterEntity( Entity _Entity );

								inline const ComponentMask& GetSystemSignature() const noexcept { return m_SystemSignature; }

				protected:
								std::vector<Entity> m_RegisteredEntities;
								ComponentMask m_SystemSignature;
				};
}
