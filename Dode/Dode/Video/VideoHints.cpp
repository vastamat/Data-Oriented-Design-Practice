#include "VideoHints.h"

#include "Logger/Logger.h"

#include <GLFW\glfw3.h>
#include <string>

namespace dode
{
				namespace
				{
								std::string HintValueToString( int32 _Value )
								{
												if ( _Value == GLFW_DONT_CARE )
												{
																return "Don't care";
												}
												else
												{
																return std::to_string( _Value );
												}
								}

								void CheckHintNumber( int32 _Value )
								{
												DENSURE( ( _Value >= GLFW_DONT_CARE ) && ( _Value <= INT_MAX ) );
								}
				}
				VideoHints::VideoHints()
								: m_FramebufferHints()
								, m_ContextHints()
								, m_WindowHints()
								, m_MonitorHints()
				{
				}
				void VideoHints::ResetToDefaults()
				{
								*this = VideoHints();
								glfwDefaultWindowHints();
				}
				void VideoHints::FromVideoMode( const void * _Vidmode )
				{
								const GLFWvidmode* vidmode = reinterpret_cast< const GLFWvidmode* >( _Vidmode );
								m_FramebufferHints.m_RedBits = vidmode->redBits;
								m_FramebufferHints.m_GreenBits = vidmode->greenBits;
								m_FramebufferHints.m_BlueBits = vidmode->blueBits;
								m_MonitorHints.m_RefreshRate = vidmode->refreshRate;
				}
				void VideoHints::Apply()
				{
								dode::Logger Logger;
								Logger.AddSink( dode::CreateConsoleSink() );

								CheckHintNumber( m_FramebufferHints.m_RedBits );
								CheckHintNumber( m_FramebufferHints.m_GreenBits );
								CheckHintNumber( m_FramebufferHints.m_BlueBits );
								CheckHintNumber( m_FramebufferHints.m_AlphaBits );
								CheckHintNumber( m_FramebufferHints.m_DepthBits );
								CheckHintNumber( m_FramebufferHints.m_StencilBits );
								CheckHintNumber( m_FramebufferHints.m_Samples );
								CheckHintNumber( m_MonitorHints.m_RefreshRate );

								glfwWindowHint( GLFW_RESIZABLE, m_WindowHints.m_Resizable ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_VISIBLE, m_WindowHints.m_Visible ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_DECORATED, m_WindowHints.m_Decorated ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_FOCUSED, m_WindowHints.m_Focused ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_AUTO_ICONIFY, m_WindowHints.m_AutoIconify ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_FLOATING, m_WindowHints.m_Floating ? GL_TRUE : GL_FALSE );

								glfwWindowHint( GLFW_RED_BITS, m_FramebufferHints.m_RedBits );
								glfwWindowHint( GLFW_GREEN_BITS, m_FramebufferHints.m_GreenBits );
								glfwWindowHint( GLFW_BLUE_BITS, m_FramebufferHints.m_BlueBits );
								glfwWindowHint( GLFW_ALPHA_BITS, m_FramebufferHints.m_AlphaBits );
								glfwWindowHint( GLFW_DEPTH_BITS, m_FramebufferHints.m_DepthBits );
								glfwWindowHint( GLFW_STENCIL_BITS, m_FramebufferHints.m_StencilBits );

								glfwWindowHint( GLFW_SAMPLES, m_FramebufferHints.m_Samples );
								glfwWindowHint( GLFW_STEREO, m_FramebufferHints.m_Stereo ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_SRGB_CAPABLE, m_FramebufferHints.m_SRGBCapable ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_DOUBLEBUFFER, m_FramebufferHints.m_DoubleBuffer ? GL_TRUE : GL_FALSE );

								glfwWindowHint( GLFW_REFRESH_RATE, m_MonitorHints.m_RefreshRate );

								int32 api = GLFW_OPENGL_API;
								int32 profile = GLFW_OPENGL_ANY_PROFILE;
								int32 robustness = GLFW_NO_ROBUSTNESS;
								int32 releaseBehavior = GLFW_ANY_RELEASE_BEHAVIOR;

								switch ( m_ContextHints.m_ClientAPI )
								{
												case ContextHints::ClientAPI::OpenGL:
												{
																api = GLFW_OPENGL_API;
																break;
												}
												case ContextHints::ClientAPI::OpenGL_ES:
												{
																api = GLFW_OPENGL_ES_API;
																break;
												}
												default:
												{
																DLOG_ERROR( Logger ) << "Unsupported openGL API: " << m_ContextHints.m_ClientAPI;
												}
								}

								switch ( m_ContextHints.m_OpenGLProfile )
								{
												case ContextHints::OpenGLProfile::Any:
												{
																profile = GLFW_OPENGL_ANY_PROFILE;
																break;
												}
												case ContextHints::OpenGLProfile::Compatibility:
												{
																profile = GLFW_OPENGL_COMPAT_PROFILE;
																break;
												}
												case ContextHints::OpenGLProfile::Core:
												{
																profile = GLFW_OPENGL_CORE_PROFILE;
																break;
												}
												default:
												{
																DLOG_ERROR( Logger ) << "Unsupported openGL profile: " << m_ContextHints.m_OpenGLProfile;
												}
								}

								switch ( m_ContextHints.m_ContextRobustness )
								{
												case ContextHints::ContextRobustness::LoseContextOnReset:
												{
																robustness = GLFW_LOSE_CONTEXT_ON_RESET;
																break;
												}
												case ContextHints::ContextRobustness::NoResetNotification:
												{
																robustness = GLFW_NO_RESET_NOTIFICATION;
																break;
												}
												case ContextHints::ContextRobustness::NoRobustness:
												{
																robustness = GLFW_NO_ROBUSTNESS;
																break;
												}
												default:
												{
																DLOG_ERROR( Logger ) << "Unsupported openGL robustness: " << m_ContextHints.m_ContextRobustness;
												}
								}

								switch ( m_ContextHints.m_ContextReleaseBehavior )
								{
												case ContextHints::ContextReleaseBehavior::Any:
												{
																releaseBehavior = GLFW_ANY_RELEASE_BEHAVIOR;
																break;
												}
												case ContextHints::ContextReleaseBehavior::Flush:
												{
																releaseBehavior = GLFW_RELEASE_BEHAVIOR_FLUSH;
																break;
												}
												case ContextHints::ContextReleaseBehavior::None:
												{
																releaseBehavior = GLFW_RELEASE_BEHAVIOR_NONE;
																break;
												}
												default:
												{
																DLOG_ERROR( Logger ) << "Unsupported context release behavior: " << m_ContextHints.m_ContextReleaseBehavior;
												}
								}

								glfwWindowHint( GLFW_CLIENT_API, api );
								glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, m_ContextHints.m_ContextVersionMajor );
								glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, m_ContextHints.m_ContextVersionMinor );

								glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, robustness );
								glfwWindowHint( GLFW_CONTEXT_RELEASE_BEHAVIOR, releaseBehavior );

								glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, m_ContextHints.m_OpenGLForwardCompatible ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, m_ContextHints.m_OpenGLDebugContext ? GL_TRUE : GL_FALSE );
								glfwWindowHint( GLFW_OPENGL_PROFILE, profile );
				}
				std::ostream & operator<<( std::ostream & _Stream, const ContextHints::ClientAPI & _ClientAPI )
				{
								switch ( _ClientAPI )
								{
												case ContextHints::ClientAPI::OpenGL:
												{
																_Stream << "OpenGL";
																break;
												}
												case ContextHints::ClientAPI::OpenGL_ES:
												{
																_Stream << "OpenGL ES";
																break;
												}
												default:
												{
																_Stream << "Unknown - " << static_cast< uint8 >( _ClientAPI );
												}
								}
								return _Stream;
				}
				std::ostream & operator<<( std::ostream & _Stream, const ContextHints::ContextRobustness & _ContextRobustness )
				{
								switch ( _ContextRobustness )
								{
												case ContextHints::ContextRobustness::LoseContextOnReset:
												{
																_Stream << "Lose Context On Reset";
																break;
												}
												case ContextHints::ContextRobustness::NoResetNotification:
												{
																_Stream << "No Reset Notification";
																break;
												}
												case ContextHints::ContextRobustness::NoRobustness:
												{
																_Stream << "No Robustness";
																break;
												}
												default:
												{
																_Stream << "Unknown - " << static_cast< uint8 >( _ContextRobustness );
												}
								}
								return _Stream;
				}
				std::ostream & operator<<( std::ostream & _Stream, const ContextHints::ContextReleaseBehavior & _ContextReleaseBehavior )
				{
								switch ( _ContextReleaseBehavior )
								{
												case ContextHints::ContextReleaseBehavior::Any:
												{
																_Stream << "Any";
																break;
												}
												case ContextHints::ContextReleaseBehavior::Flush:
												{
																_Stream << "Flush";
																break;
												}
												case ContextHints::ContextReleaseBehavior::None:
												{
																_Stream << "None";
																break;
												}
												default:
												{
																_Stream << "Unknown - " << static_cast< uint8 >( _ContextReleaseBehavior );
												}
								}
								return _Stream;
				}
				std::ostream & operator<<( std::ostream & _Stream, const ContextHints::OpenGLProfile & _OpenGLProfile )
				{
								switch ( _OpenGLProfile )
								{
												case ContextHints::OpenGLProfile::Any:
												{
																_Stream << "Any";
																break;
												}
												case ContextHints::OpenGLProfile::Compatibility:
												{
																_Stream << "Compatibility";
																break;
												}
												case ContextHints::OpenGLProfile::Core:
												{
																_Stream << "Core";
																break;
												}
												default:
												{
																_Stream << "Unknown - " << static_cast< uint8 >( _OpenGLProfile );
												}
								}
								return _Stream;
				}
				std::ostream & operator<<( std::ostream & _Stream, const VideoHints & _Hints )
				{
								_Stream << std::boolalpha
												<< "\tWindow hints:"
												<< "\n\tResizable: " << _Hints.m_WindowHints.m_Resizable
												<< "\n\tVisible: " << _Hints.m_WindowHints.m_Resizable
												<< "\n\tDecorated: " << _Hints.m_WindowHints.m_Decorated
												<< "\n\tFocused: " << _Hints.m_WindowHints.m_Focused
												<< "\n\tAutoIconify: " << _Hints.m_WindowHints.m_AutoIconify
												<< "\n\tFloating: " << _Hints.m_WindowHints.m_Floating

												<< "\n\tBits:"
												<< " | r: " << HintValueToString( _Hints.m_FramebufferHints.m_RedBits )
												<< " | g: " << HintValueToString( _Hints.m_FramebufferHints.m_GreenBits )
												<< " | b: " << HintValueToString( _Hints.m_FramebufferHints.m_BlueBits )
												<< " | a: " << HintValueToString( _Hints.m_FramebufferHints.m_AlphaBits )
												<< " | depth: " << HintValueToString( _Hints.m_FramebufferHints.m_DepthBits )
												<< " | stencil: " << HintValueToString( _Hints.m_FramebufferHints.m_StencilBits )

												<< "\n\tStereo: " << _Hints.m_FramebufferHints.m_Stereo
												<< "\n\tSamples: " << HintValueToString( _Hints.m_FramebufferHints.m_Samples )
												<< "\n\tsRGB: " << _Hints.m_FramebufferHints.m_SRGBCapable
												<< "\n\tDoubleBuffer: " << _Hints.m_FramebufferHints.m_DoubleBuffer
												<< "\n\tRefreshRate: " << HintValueToString( _Hints.m_MonitorHints.m_RefreshRate )
												<< "\n\tClientAPI: " << _Hints.m_ContextHints.m_ClientAPI
												<< " v" << _Hints.m_ContextHints.m_ContextVersionMajor
												<< "." << _Hints.m_ContextHints.m_ContextVersionMinor
												<< "\n\tForwardCompatible: " << _Hints.m_ContextHints.m_OpenGLForwardCompatible
												<< "\n\tContextRobustness: " << _Hints.m_ContextHints.m_ContextRobustness
												<< "\n\tContextReleaseBehavior: " << _Hints.m_ContextHints.m_ContextReleaseBehavior;

								return _Stream;
				}
}