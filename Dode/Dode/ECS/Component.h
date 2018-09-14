#pragma once

#include "Core/CommonIncludes.h"

#include <type_traits>

namespace internal
{
				inline dode::uint32 GetUniqueComponentId()
				{
								static dode::uint32 s_UniqueComponentIdCounter = 0;
								return s_UniqueComponentIdCounter++;
				}
}

namespace dode
{
				struct Component
				{
				};

				template<typename ComponentType>
				uint32 GetIdOfComponentType()
				{
								static_assert( std::is_base_of<Component, ComponentType>::value, "Must inherit from Component" );
								static_assert( std::is_standard_layout<ComponentType>::value, "Must have standard layout (all public, no virtual functions)" );

								static uint32 s_ComponentTypeId = internal::GetUniqueComponentId();
								return s_ComponentTypeId;
				}
}