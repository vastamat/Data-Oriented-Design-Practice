#pragma once

#include "Core/CommonIncludes.h"

#include <cmath>

namespace dode
{
				namespace Math
				{
								constexpr float c_Pi = 3.1415926535897932f;
								constexpr float c_TwoPi = 6.28318530717959f;
								constexpr float c_HalfPi = 1.57079632679f;
								constexpr float c_ReciprocalPi = 0.31830988618f;
								constexpr float c_ReciprocalTwoPi = 0.159154943091895f;
								constexpr float c_ReciprocalHalfPi = 0.636619772367581f;

								constexpr float c_EulersNumber = 2.71828182845904523536f;
								constexpr float c_Log2E = 1.44269504088896f;
								constexpr float c_RadToDeg = 57.2957795130823f; // 180.0f/PI;
								constexpr float c_DegToRad = 0.0174532925199433f; // PI/180.0f;

								constexpr inline int32 TruncToInt( float _Val )
								{
												return ( int32 )_Val;
								}

								constexpr inline float TruncToFloat( float _Val )
								{
												return ( float )TruncToInt( _Val );
								}

								inline float FloorToFloat( float _Val )
								{
												return std::floorf( _Val );
								}

								inline int32 FloorToInt( float _Val )
								{
												return TruncToInt( FloorToFloat( _Val ) );
								}

								inline double FloorToDouble( double _Val )
								{
												return std::floor( _Val );
								}

								inline int32 CeilToInt( float _Val )
								{
												return TruncToInt( std::ceilf( _Val ) );
								}

								inline int32 RoundToInt( float _Val )
								{
												return CeilToInt( _Val - 0.5f );
								}

								inline float CeilToFloat( float _Val )
								{
												return std::ceilf( _Val );
								}

								inline float RoundToFloat( float _Val )
								{
												return CeilToFloat( _Val - 0.5f );
								}

								inline double CeilToDouble( double _Val )
								{
												return std::ceil( _Val );
								}

								inline float Fractional( float _Val )
								{
												return _Val - TruncToFloat( _Val );
								}

								inline float Exp( float _Val ) { return std::expf( _Val ); }
								inline float Log( float _Val ) { return std::logf( _Val ); }
								inline float Logx( float _Val, float base ) { return Log( _Val ) / Log( base ); }
								inline float Log2( float _Val ) { return Log( _Val ) * c_Log2E; }

								inline float Fmod( float num, float _Den ) { return std::fmodf( num, _Den ); }
								inline float Sin( float _Val ) { return std::sinf( _Val ); }
								inline float ASin( float _Val ) { return std::asinf( _Val ); }
								inline float Cos( float _Val ) { return std::cosf( _Val ); }
								inline float ACos( float _Val ) { return std::acosf( _Val ); }
								inline float Tan( float _Val ) { return std::tanf( _Val ); }
								inline float ATan( float _Val ) { return std::atanf( _Val ); }
								inline float ATan2( float _Val, float _Val2 ) { return std::atan2f( _Val, _Val2 ); }
								inline float Pow( float _Val, float _Power ) { return std::powf( _Val, _Power ); }
								inline float Sqrt( float _Val ) { return std::sqrtf( _Val ); }

								inline float Reciprocal( float _Val ) { return 1.0f / _Val; }

								inline float ReciprocalSqrt( float _Val ) { return Reciprocal( sqrtf( _Val ) ); }

								inline bool IsPowerOfTwo( uint32_t _Val )
								{
												return ( _Val != 0u ) && ( ( _Val & ( _Val - 1u ) ) == 0u );
								}

								template<typename T>
								constexpr inline T Absolute( const T& _Val )
								{
												return _Val >= static_cast< T >( 0 ) ? _Val : -_Val;
								}

								template<typename T>
								constexpr inline T Min( const T& _Val1, const T& _Val2 )
								{
												return _Val1 <= _Val2 ? _Val1 : _Val2;
								}

								template<typename T>
								constexpr inline T Min3( const T& _Val1, const T& _Val2, const T& _Val3 )
								{
												return Min( Min( _Val1, _Val2 ), _Val3 );
								}

								template<typename T>
								constexpr inline T Max( const T& _Val1, const T& _Val2 )
								{
												return _Val1 >= _Val2 ? _Val1 : _Val2;
								}

								template<typename T>
								constexpr inline T Max3( const T& _Val1, const T& _Val2, const T& _Val3 )
								{
												return Max( Max( _Val1, _Val2 ), _Val3 );
								}

								template<typename T>
								inline T ToDegrees( const T& _Val )
								{
												return _Val * c_RadToDeg;
								}

								template<typename T>
								inline T ToRadians( const T& _Val )
								{
												return _Val * c_DegToRad;
								}

								template<typename T, typename U>
								inline T Lerp( const T& _Src, const T& _Dst, const U& _Alpha )
								{
												return static_cast< T >( ( _Src * ( static_cast< U >( 1 ) - _Alpha ) ) + _Dst * _Alpha );
								}

								template<typename T>
								inline T Clamp( const T& _Val, const T& _Min, const T& _Max )
								{
												if ( _Val > _Max )
												{
																return _Max;
												}
												else if ( _Val > _Min )
												{
																return _Val;
												}
												else
												{
																return _Min;
												}
								}

								template<typename T>
								inline T Square( const T& _Val )
								{
												return _Val * _Val;
								}

								template<typename T>
								inline T Cube( const T& _Val )
								{
												return _Val * _Val * _Val;
								}

								template<typename T>
								inline bool Equals( const T& _Val1, const T& _Val2, const T& _ErrorMargin )
								{
												return Absolute( _Val1 - _Val2 ) < _ErrorMargin;
								}
				}
}

template<>
inline float dode::Math::Absolute( const float& _Val )
{
				return std::fabsf( _Val );
}