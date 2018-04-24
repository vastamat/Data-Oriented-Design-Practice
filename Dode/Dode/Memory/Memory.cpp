#include "Memory.h"

#include "../Math/Math.h"

#include <cstdlib>

namespace dode
{
				namespace Memory
				{
								void * Malloc( uintptr _Size, uint32 _Alignment )
								{
												_Alignment = Math::Max( _Size >= 16 ? 16u : 8u, _Alignment );
												void* ptr = std::malloc( _Size + _Alignment + sizeof( void* ) + sizeof( uintptr ) );
												void* result = Align( ( uint8* )ptr + sizeof( void* ) + sizeof( uintptr ), ( uintptr )_Alignment );
												*( ( void** )( ( uint8* )result - sizeof( void* ) ) ) = ptr;
												*( ( uintptr* )( ( uint8* )result - sizeof( void* ) - sizeof( uintptr ) ) ) = _Alignment;
												return result;
								}

								void * Realloc( void * _Ptr, uintptr _Size, uint32 _Alignment )
								{
												_Alignment = Math::Max( _Size >= 16 ? 16u : 8u, _Alignment );
												if ( _Ptr == nullptr )
												{
																return Memory::Malloc( _Size, _Alignment );
												}

												if ( _Size == 0 )
												{
																Memory::Free( _Ptr );
																return nullptr;
												}

												void* result = Memory::Malloc( _Size, _Alignment );
												uintptr allocSize = Memory::GetAllocSize( _Ptr );
												Memory::MemCpy( result, _Ptr, Math::Min( allocSize, _Size ) );
												Memory::Free( _Ptr );

												return result;
								}

								void * Free( void * _Ptr )
								{
												if ( _Ptr )
												{
																std::free( *( ( void** )( ( uint8* )_Ptr - sizeof( void* ) ) ) );
												}
												return nullptr;
								}

								uintptr GetAllocSize( void * _Ptr )
								{
												return *( ( uintptr* )( ( uint8* )_Ptr - sizeof( void* ) - sizeof( uintptr ) ) );
								}
				}
}