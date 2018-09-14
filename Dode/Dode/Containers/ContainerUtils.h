#pragma once

#include "Core/CommonIncludes.h"

#include <algorithm>
#include <utility>

namespace dode
{
				template<typename Container>
				void SwapAndPop( Container& _Container, uint32 _Index )
				{
								std::swap( _Container[_Index], _Container.back() );
								_Container.pop_back();
				}

				template<typename Container, typename ElementType>
				void RemoveErase( Container& _Container, const ElementType& _Element )
				{
								auto removeStartIter = std::remove( _Container.begin(), _Container.end(), _Element );

								_Container.erase( removeStartIter, _Container.end() );
				}
}