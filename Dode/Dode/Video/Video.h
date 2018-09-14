#pragma once

#include "VideoHints.h"
#include "Window.h"

namespace dode
{
				class Video
				{
				public:
								void Initialize( uint32 _Width, uint32 _Height, bool _Fullscreen, bool _Borderless );
								void Shutdown();
								
								void PollEvents();
								void SwapBuffers();

								void CreateFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor, int32 _Width, int32 _Height );
								void CreateBorderlessFullscreenWindow( const std::string & _Title, GLFWmonitor * _Monitor );
								void CreateWindowedWindow( const std::string & _Title, int32 _Width, int32 _Height );

				private:
								Window m_MainWindow;
				};
}
