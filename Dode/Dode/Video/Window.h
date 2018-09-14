#pragma once

#include "Core/CommonIncludes.h"

#include <string>

struct GLFWmonitor;
struct GLFWwindow;

namespace dode
{
				class Window
				{
				public:
								struct Frame
								{
												int32 m_Left{ 0 };
												int32 m_Top{ 0 };
												int32 m_Right{ 0 };
												int32 m_Bottom{ 0 };
								};
								struct ScreenPosition
								{
												int32 m_X{ 0 };
												int32 m_Y{ 0 };
								};
								struct ScreenSize
								{
												int32 m_Width{ 0 };
												int32 m_Height{ 0 };
								};
				public:
								Window();

								Window( const Window& ) = delete;
								Window& operator = ( const Window& ) = delete;

								Window( Window&& _Other );
								Window& operator = ( Window&& _Rhs );

								~Window();

								void CreateFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor, int32 _Width, int32 _Height );
								void CreateBorderlessFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor );
								void CreateWindowedWindow( const std::string & _Title, int32 _Width, int32 _Height );
								void Close();

								bool ShouldClose() const;

								void SetShouldClose( bool _Value );
								void SetTitle( const std::string& _Title );
								void SetPosition( const ScreenPosition& _Position );
								void SetSize( const ScreenSize& _Size );

								void Iconify();
								void Restore();
								void Show();
								void Hide();

								void MakeCurrent();
								void SwapBuffers();

								ScreenPosition GetPosition() const;
								ScreenSize GetSize() const;
								ScreenSize GetFramebufferSize() const;
								Frame GetFrame() const;

								bool IsFocused() const;
								bool IsIconified() const;
								bool IsVisible() const;
								bool IsResizable() const;
								bool IsDecorated() const;
								bool IsFloating() const;

				private:
								std::string m_Title;

								ScreenPosition m_Position;
								ScreenSize m_Size;
						
								GLFWwindow * m_Handle;
				};
}