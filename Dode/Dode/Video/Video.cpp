#include "Video.h"

#include "../Logger/Logger.h"

#include <GLFW\glfw3.h>

namespace dode
{
				namespace
				{
								std::string IntepretGLFWerrorcode( int32 _Code )
								{
												switch ( _Code )
												{
																case GLFW_NOT_INITIALIZED:		return "GLFW has not been initialized";
																case GLFW_NO_CURRENT_CONTEXT:	return "No context is current for this thread";
																case GLFW_INVALID_ENUM:			return "One of the arguments to the function was an invalid enum value";
																case GLFW_INVALID_VALUE:		return "One of the arguments to the function was an invalid value";
																case GLFW_OUT_OF_MEMORY:		return "A memory allocation failed";
																case GLFW_API_UNAVAILABLE:		return "GLFW could not find support for the requested client API on the system";
																case GLFW_VERSION_UNAVAILABLE:	return "The requested OpenGL or OpenGL ES version is not available";
																case GLFW_PLATFORM_ERROR:		return "A platform - specific error occurred that does not match any of the more specific categories";
																case GLFW_FORMAT_UNAVAILABLE:	return "The requested format is not supported or available";
																default: return std::string( "Unknown error code: " ) + std::to_string( _Code );
												}
								}

								void GLFWErrorCallback( int32 _Error, const char* _Description )
								{
												dode::Logger Logger;
												Logger.AddSink( dode::CreateConsoleSink() );
												DLOG_ERROR( Logger ) << "GLFW error (" << IntepretGLFWerrorcode( _Error ) << "): " << _Description;
								}
				}

				void Video::Initialize( uint32 _Width, uint32 _Height, bool _Fullscreen, bool _Borderless )
				{
								glfwSetErrorCallback( &GLFWErrorCallback );
								
								if ( !glfwInit() )
								{
												throw std::runtime_error( "Failed to initialize GLFW" );
								}

								dode::Logger Logger;
								Logger.AddSink( dode::CreateConsoleSink() );

								DLOG_DEBUG( Logger ) << "GLFW v" << glfwGetVersionString();

								m_Hints.m_WindowHints.m_Resizable = true;
								m_Hints.m_WindowHints.m_Visible = true;
								m_Hints.m_WindowHints.m_Decorated = true;
								m_Hints.m_WindowHints.m_Focused = true;
								m_Hints.m_WindowHints.m_AutoIconify = true;
								m_Hints.m_WindowHints.m_Floating = false;

								GLFWmonitor* monitor = glfwGetPrimaryMonitor();

								m_Hints.FromVideoMode( glfwGetVideoMode( monitor ) );

								m_Hints.m_FramebufferHints.m_Stereo = false;
								m_Hints.m_FramebufferHints.m_Samples = 0;
								m_Hints.m_FramebufferHints.m_SRGBCapable = true;
								m_Hints.m_FramebufferHints.m_DoubleBuffer = true;

								m_Hints.m_ContextHints.m_ClientAPI = ContextHints::ClientAPI::OpenGL;
								m_Hints.m_ContextHints.m_ContextVersionMajor = 4;
								m_Hints.m_ContextHints.m_ContextVersionMinor = 0;

								m_Hints.m_ContextHints.m_OpenGLForwardCompatible = true;
								m_Hints.m_ContextHints.m_OpenGLProfile = ContextHints::OpenGLProfile::Core;
#ifdef _DEBUG
								m_Hints.m_ContextHints.m_OpenGLDebugContext = true;
#else
								m_Hints.m_OpenGLDebugContext = false;
#endif
								m_Hints.m_ContextHints.m_ContextRobustness = ContextHints::ContextRobustness::NoRobustness;
								m_Hints.m_ContextHints.m_ContextReleaseBehavior = ContextHints::ContextReleaseBehavior::Any;

								DLOG_DEBUG( Logger ) << m_Hints;

								m_Hints.Apply();

								if ( _Fullscreen )
								{
												if ( _Borderless )
												{
																CreateBorderlessFullscreenWindow( "Borderless Fullscreen", monitor );
												}
												else
												{
																CreateFullscreenWindow( "Borderless Fullscreen", monitor, _Width, _Height );
												}
								}
								else
								{
												CreateWindowedWindow( "Borderless Fullscreen", _Width, _Height );
								}
				}
				void Video::Shutdown()
				{
								m_MainWindow.reset();
								glfwTerminate();
				}
				void Video::PollEvents()
				{
								glfwPollEvents();
				}
				void Video::SwapBuffers()
				{
								m_MainWindow->SwapBuffers();
				}
				void Video::CreateFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor, int32 _Width, int32 _Height )
				{
								m_MainWindow.reset( new Window( _Title, _Monitor, _Width, _Height ) );
				}
				void Video::CreateBorderlessFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor )
				{
								m_MainWindow.reset( new Window( _Title, _Monitor ) );
				}
				void Video::CreateWindowedWindow( const std::string & _Title, int32 _Width, int32 _Height )
				{
								m_MainWindow.reset( new Window( _Title, _Width, _Height ) );
				}
}