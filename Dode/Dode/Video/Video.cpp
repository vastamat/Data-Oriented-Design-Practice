#include "Video.h"

#include "Logger/Logger.h"
#include "Core/FileIO.h"

#include <GLFW\glfw3.h>

#include <iostream>

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

				void Video::Initialize()
				{
								nlohmann::json settings;
								FileIO::ReadFileToJsonObject( settings, "Engine/Config/Video.json" );

								const uint32 width = settings["Width"];
								const uint32 height = settings["Height"];
								const bool fullscreen = settings["Fullscreen"];
								const bool borderless = settings["Borderless"];

								glfwSetErrorCallback( &GLFWErrorCallback );
								
								if ( !glfwInit() )
								{
												throw std::runtime_error( "Failed to initialize GLFW" );
								}

								dode::Logger Logger;
								Logger.AddSink( dode::CreateConsoleSink() );

								DLOG_DEBUG( Logger ) << "GLFW v" << glfwGetVersionString();

								VideoHints videoHints;
								videoHints.m_WindowHints.m_Resizable = true;
								videoHints.m_WindowHints.m_Visible = true;
								videoHints.m_WindowHints.m_Decorated = true;
								videoHints.m_WindowHints.m_Focused = true;
								videoHints.m_WindowHints.m_AutoIconify = true;
								videoHints.m_WindowHints.m_Floating = false;

								GLFWmonitor* monitor = glfwGetPrimaryMonitor();

								videoHints.FromVideoMode( glfwGetVideoMode( monitor ) );

								videoHints.m_FramebufferHints.m_Stereo = false;
								videoHints.m_FramebufferHints.m_Samples = 0;
								videoHints.m_FramebufferHints.m_SRGBCapable = true;
								videoHints.m_FramebufferHints.m_DoubleBuffer = true;

								videoHints.m_ContextHints.m_ClientAPI = ContextHints::ClientAPI::OpenGL;
								videoHints.m_ContextHints.m_ContextVersionMajor = 4;
								videoHints.m_ContextHints.m_ContextVersionMinor = 0;

								videoHints.m_ContextHints.m_OpenGLForwardCompatible = true;
								videoHints.m_ContextHints.m_OpenGLProfile = ContextHints::OpenGLProfile::Core;
#ifdef _DEBUG
								videoHints.m_ContextHints.m_OpenGLDebugContext = true;
#else
								videoHints.m_OpenGLDebugContext = false;
#endif
								videoHints.m_ContextHints.m_ContextRobustness = ContextHints::ContextRobustness::NoRobustness;
								videoHints.m_ContextHints.m_ContextReleaseBehavior = ContextHints::ContextReleaseBehavior::Any;

								DLOG_DEBUG( Logger ) << videoHints;

								videoHints.Apply();

								if ( fullscreen )
								{
												if ( borderless )
												{
																CreateBorderlessFullscreenWindow( "Borderless Fullscreen", monitor );
												}
												else
												{
																CreateFullscreenWindow( "Borderless Fullscreen", monitor, width, height );
												}
								}
								else
								{
												CreateWindowedWindow( "Borderless Fullscreen", width, height );
								}
				}
				void Video::Shutdown()
				{
								m_MainWindow.Close();
								glfwTerminate();
				}
				void Video::PollEvents()
				{
								glfwPollEvents();
				}
				void Video::SwapBuffers()
				{
								m_MainWindow.SwapBuffers();
				}
				void Video::CreateFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor, int32 _Width, int32 _Height )
				{
								m_MainWindow.Close();
								m_MainWindow.CreateFullscreenWindow( _Title, _Monitor, _Width, _Height );
				}
				void Video::CreateBorderlessFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor )
				{
								m_MainWindow.Close();
								m_MainWindow.CreateBorderlessFullscreenWindow( _Title, _Monitor );
				}
				void Video::CreateWindowedWindow( const std::string & _Title, int32 _Width, int32 _Height )
				{
								m_MainWindow.Close();
								m_MainWindow.CreateWindowedWindow( _Title, _Width, _Height );
				}
}