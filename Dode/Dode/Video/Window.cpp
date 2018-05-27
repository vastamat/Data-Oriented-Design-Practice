#include "Window.h"

#include "../Core/Engine.h"
#include "../EventSystem/EventDispatcher.h"

#include <GLFW/glfw3.h>

namespace dode
{
				void FramebufferSizeCallback( GLFWwindow* _Handle, int32 _Width, int32 _Height )
				{
								Window* w = static_cast< Window* >( glfwGetWindowUserPointer( _Handle ) );
								assert( w );
								//Channel::broadcast( Window::OnFramebufferResized{ w, _Width, _Height } );
				}

				void WindowCloseCallback( GLFWwindow* _Handle )
				{
								EventDispatcher::BroadcastEvent( Engine::OnExit() );
				}

				void WindowFocusCallback( GLFWwindow* _Handle, int32 _State )
				{
								Window* w = static_cast< Window* >( glfwGetWindowUserPointer( _Handle ) );
								assert( w );

								/*switch ( _State )
								{
												case GL_TRUE:
																Channel::broadcast( Window::OnFocused{ w } );
																break;

												case GL_FALSE:
																Channel::broadcast( Window::OnFocusLost{ w } );
																break;

												default:
																gLogWarning << "Unsupported window focus _State from callback: " << _State;
								}*/
				}

				void WindowIconifyCallback( GLFWwindow* _Handle, int32 _State )
				{
								Window* w = static_cast< Window* >( glfwGetWindowUserPointer( _Handle ) );
								assert( w );

								/*switch ( _State )
								{
												case GL_TRUE:
																Channel::broadcast( Window::OnIconify{ w } );
																break;

												case GL_FALSE:
																Channel::broadcast( Window::OnRestore{ w } );
																break;

												default:
																gLogWarning << "Unsupported window iconify _State from callback: " << _State;
								}*/
				}

				void WindowPositionCallback( GLFWwindow* _Handle, int32 _X, int32 _Y )
				{
								Window* w = static_cast< Window* >( glfwGetWindowUserPointer( _Handle ) );
								assert( w );

								//auto oldPosition = w->getPosition();

								//Channel::broadcast( Window::OnMoved{ w, oldPosition.first, oldPosition.second, x, y } );
				}

				void WindowRefreshCallback( GLFWwindow* _Handle )
				{
								Window* w = static_cast< Window* >( glfwGetWindowUserPointer( _Handle ) );
								assert( w );

								//Channel::broadcast( Window::OnRefreshed{ w } );
				}

				void WindowResizeCallback( GLFWwindow* _Handle, int _Width, int _Height )
				{
								Window* w = static_cast< Window* >( glfwGetWindowUserPointer( _Handle ) );
								assert( w );

								/*auto oldSize = w->getSize();
								Channel::broadcast( Window::OnResized{ w, oldSize.first, oldSize.second, _Width, _Height } );*/
				}

				// windowed mode (on primary monitor)
				Window::Window( const std::string & _Title, int32 _Width, int32 _Height )
								: m_Title( _Title )
								, m_Position()
								, m_Size{ _Width, _Height }
								, m_Handle( nullptr )
				{
								m_Handle = glfwCreateWindow( m_Size.m_Width, m_Size.m_Height, m_Title.c_str(), nullptr, nullptr );
								glfwSetWindowUserPointer( m_Handle, this );

								glfwGetWindowPos( m_Handle, &m_Position.m_X, &m_Position.m_Y );
								glfwSetFramebufferSizeCallback( m_Handle, &FramebufferSizeCallback );
								glfwSetWindowCloseCallback( m_Handle, &WindowCloseCallback );
								glfwSetWindowFocusCallback( m_Handle, &WindowFocusCallback );
								glfwSetWindowIconifyCallback( m_Handle, &WindowIconifyCallback );
								glfwSetWindowPosCallback( m_Handle, &WindowPositionCallback );
								glfwSetWindowRefreshCallback( m_Handle, &WindowRefreshCallback );
								glfwSetWindowSizeCallback( m_Handle, &WindowResizeCallback );

								MakeCurrent();
				}

				// borderless fullscreen mode
				Window::Window( const std::string & _Title, GLFWmonitor * _Monitor )
								: m_Title( _Title )
								, m_Position()
								, m_Size()
								, m_Handle( nullptr )
				{
								auto* videMode = glfwGetVideoMode( _Monitor );

								m_Size.m_Width = videMode->width;
								m_Size.m_Height = videMode->height;

								m_Handle = glfwCreateWindow( m_Size.m_Width, m_Size.m_Height, m_Title.c_str(), _Monitor, nullptr );
								glfwSetWindowUserPointer( m_Handle, this );
								glfwGetWindowPos( m_Handle, &m_Position.m_X, &m_Position.m_Y );

								glfwSetFramebufferSizeCallback( m_Handle, &FramebufferSizeCallback );
								glfwSetWindowCloseCallback( m_Handle, &WindowCloseCallback );
								glfwSetWindowFocusCallback( m_Handle, &WindowFocusCallback );
								glfwSetWindowIconifyCallback( m_Handle, &WindowIconifyCallback );
								glfwSetWindowPosCallback( m_Handle, &WindowPositionCallback );
								glfwSetWindowRefreshCallback( m_Handle, &WindowRefreshCallback );
								glfwSetWindowSizeCallback( m_Handle, &WindowResizeCallback );

								MakeCurrent();
				}

				// fullscreen mode
				Window::Window( const std::string & _Title, GLFWmonitor * _Monitor, int32 _Width, int32 _Height )
								: m_Title( _Title )
								, m_Position()
								, m_Size{ _Width, _Height }
								, m_Handle( nullptr )
				{
								m_Handle = glfwCreateWindow( m_Size.m_Width, m_Size.m_Height, m_Title.c_str(), _Monitor, nullptr );
								glfwSetWindowUserPointer( m_Handle, this );
								glfwGetWindowPos( m_Handle, &m_Position.m_X, &m_Position.m_Y );

								glfwSetFramebufferSizeCallback( m_Handle, &FramebufferSizeCallback );
								glfwSetWindowCloseCallback( m_Handle, &WindowCloseCallback );
								glfwSetWindowFocusCallback( m_Handle, &WindowFocusCallback );
								glfwSetWindowIconifyCallback( m_Handle, &WindowIconifyCallback );
								glfwSetWindowPosCallback( m_Handle, &WindowPositionCallback );
								glfwSetWindowRefreshCallback( m_Handle, &WindowRefreshCallback );
								glfwSetWindowSizeCallback( m_Handle, &WindowResizeCallback );

								MakeCurrent();
				}
				Window::Window( Window && _Other )
								: m_Title( std::move( _Other.m_Title ) )
								, m_Position( std::move( _Other.m_Position ) )
								, m_Size( std::move( _Other.m_Size ) )
								, m_Handle( std::move( _Other.m_Handle ) )
				{
								_Other.m_Handle = nullptr;

								if ( m_Handle )
								{
												glfwSetWindowUserPointer( m_Handle, this );
								}

								MakeCurrent();
				}
				Window & Window::operator=( Window && _Rhs )
				{
								if ( m_Handle )
								{
												glfwDestroyWindow( m_Handle );
								}

								m_Title = std::move( _Rhs.m_Title );
								m_Position = std::move( _Rhs.m_Position );
								m_Size = std::move( _Rhs.m_Size );
								m_Handle = std::move( _Rhs.m_Handle );

								if ( m_Handle )
								{
												glfwSetWindowUserPointer( m_Handle, this );
								}

								MakeCurrent();

								return *this;
				}
				Window::~Window()
				{
								if ( m_Handle )
								{
												glfwDestroyWindow( m_Handle );
												m_Handle = nullptr;
								}
				}
				bool Window::ShouldClose() const
				{
								return glfwWindowShouldClose( m_Handle ) != GLFW_FALSE;
				}
				void Window::SetShouldClose( bool _Value )
				{
								glfwSetWindowShouldClose( m_Handle, _Value ? GLFW_TRUE : GLFW_FALSE );
				}
				void Window::SetTitle( const std::string & _Title )
				{
								m_Title = _Title;
								glfwSetWindowTitle( m_Handle, _Title.c_str() );
				}
				void Window::SetPosition( const ScreenPosition & _Position )
				{
								glfwSetWindowPos( m_Handle, _Position.m_X, m_Position.m_Y );
				}
				void Window::SetSize( const ScreenSize & _Size )
				{
								glfwSetWindowSize( m_Handle, _Size.m_Width, _Size.m_Height );
				}
				void Window::Iconify()
				{
								glfwIconifyWindow( m_Handle );
				}
				void Window::Restore()
				{
								glfwRestoreWindow( m_Handle );
				}
				void Window::Show()
				{
								glfwShowWindow( m_Handle );
				}
				void Window::Hide()
				{
								glfwHideWindow( m_Handle );
				}
				void Window::MakeCurrent()
				{
								glfwMakeContextCurrent( m_Handle );
				}
				void Window::SwapBuffers()
				{
								glfwSwapBuffers( m_Handle );
				}
				Window::ScreenPosition Window::GetPosition() const
				{
								return m_Position;
				}
				Window::ScreenSize Window::GetSize() const
				{
								return m_Size;
				}
				Window::ScreenSize Window::GetFramebufferSize() const
				{
								ScreenSize framebufferSize;
								glfwGetFramebufferSize( m_Handle, &framebufferSize.m_Width, &framebufferSize.m_Height );
								return framebufferSize;
				}
				Window::Frame Window::GetFrame() const
				{
								Frame result;

								glfwGetWindowFrameSize( m_Handle, &result.m_Left, &result.m_Top, &result.m_Right, &result.m_Bottom );

								return result;
				}
				bool Window::IsFocused() const
				{
								return glfwGetWindowAttrib( m_Handle, GLFW_FOCUSED ) != GLFW_FALSE;
				}
				bool Window::IsIconified() const
				{
								return glfwGetWindowAttrib( m_Handle, GLFW_ICONIFIED ) != GLFW_FALSE;
				}
				bool Window::IsVisible() const
				{
								return glfwGetWindowAttrib( m_Handle, GLFW_VISIBLE ) != GLFW_FALSE;
				}
				bool Window::IsResizable() const
				{
								return glfwGetWindowAttrib( m_Handle, GLFW_RESIZABLE ) != GLFW_FALSE;
				}
				bool Window::IsDecorated() const
				{
								return glfwGetWindowAttrib( m_Handle, GLFW_DECORATED ) != GLFW_FALSE;
				}
				bool Window::IsFloating() const
				{
								return glfwGetWindowAttrib( m_Handle, GLFW_FLOATING ) != GLFW_FALSE;
				}
}