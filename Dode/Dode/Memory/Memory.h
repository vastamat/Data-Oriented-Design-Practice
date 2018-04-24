#pragma once

#include "../Core/CommonIncludes.h"

#include <cstring>

namespace dode
{
				namespace Memory
				{
								inline void* MemMove( void* _Dest, const void* _Src, uintptr _Size )
								{
												return std::memmove( _Dest, _Src, _Size );
								}

								inline int32 MemCmp( const void* _Dest, const void* _Src, uintptr _Size )
								{
												return std::memcmp( _Dest, _Src, _Size );
								}

								template<typename T>
								inline void* MemSet( void* _DestIn, T _Value, uintptr _Size )
								{
												T* _Dest = ( T* )_DestIn;
												uintptr sizeT = _Size / sizeof( T );
												uintptr remainder = _Size % sizeof( T );

												for ( uintptr i = 0; i < sizeT; ++i, ++_Dest )
												{
																std::memcpy( _Dest, &_Value, sizeof( T ) );
												}
												std::memcpy( _Dest, &_Value, remainder );

												return _DestIn;
								}

								inline void* MemZero( void* _Dest, uintptr _Size )
								{
												return std::memset( _Dest, 0, _Size );
								}

								inline void* MemCpy( void* _Dest, const void* _Src, uintptr _Size )
								{
												return std::memcpy( _Dest, _Src, _Size );
								}

								template<typename T>
								inline constexpr T Align( const T _Ptr, uintptr _Alignment )
								{
												return ( T )( ( ( intptr )_Ptr + _Alignment - 1 ) & ~( _Alignment - 1 ) );
								}

								void* Malloc( uintptr _Size, uint32 _Alignment );
								void* Realloc( void* _Ptr, uintptr _Size, uint32 _Alignment );
								void* Free( void* _Ptr );
								uintptr GetAllocSize( void* _Ptr );
				}
}