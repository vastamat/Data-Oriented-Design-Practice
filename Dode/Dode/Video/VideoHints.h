#pragma once

#include "../Core/CommonIncludes.h"

#include <ostream>

namespace dode
{
				struct ContextHints
				{
								enum class ClientAPI : uint8
								{
												OpenGL,
												OpenGL_ES
								};

								friend std::ostream& operator << ( std::ostream& _Stream, const ClientAPI& _ClientAPI );

								enum class ContextRobustness : uint8
								{
												NoRobustness,
												NoResetNotification,
												LoseContextOnReset
								};

								friend std::ostream& operator << ( std::ostream& _Stream, const ContextRobustness& _ContextRobustness );

								enum class ContextReleaseBehavior : uint8
								{
												Any,		// the default behavior of the context creation API will be used
												Flush,		// the pipeline will be flushed whenever the context is released from being the current one
												None		// the pipeline will not be flushed on release
								};

								friend std::ostream& operator << ( std::ostream& _Stream, const ContextReleaseBehavior& _ContextReleaseBehavior );

								enum class OpenGLProfile : uint8
								{
												Any,
												Compatibility,
												Core
								};

								friend std::ostream& operator << ( std::ostream& _Stream, const OpenGLProfile& _OpenGLProfile );

								// specifies which client API to create the context for. This is a hard constraint
								ClientAPI m_ClientAPI = ClientAPI::OpenGL;
								// specify the client API version that the created context must be compatible with. The exact behavior of these hints depend on the requested client API
								int32 m_ContextVersionMajor = 1;
								int32 m_ContextVersionMinor = 0;

								// specifies which OpenGL profile to create the context for. When requesting an openGL profile below v3.2 you must use ANY_PROFILE. If OpenGL ES is requested, this hint is ignored
								OpenGLProfile m_OpenGLProfile = OpenGLProfile::Any;

								// specifies the robustness strategy to be used by the context
								ContextRobustness m_ContextRobustness = ContextRobustness::NoRobustness;

								// specifies the release behavior to be used by the context
								ContextReleaseBehavior m_ContextReleaseBehavior = ContextReleaseBehavior::Any;

								// specifies whether the OpenGL context should be forward-compatible, i.e. one where all functionality deprecated in the requested version of OpenGL is removed. This may only be used if the requested OpenGL version is 3.0 or above. If OpenGL ES is requested, this hint is ignored
								bool m_OpenGLForwardCompatible = false;

								// specifies whether to create a debug OpenGL context, which may have additional error and performance issue reporting functionality. If OpenGL ES is requested, this hint is ignored
								bool m_OpenGLDebugContext = false;
				};

				struct WindowHints
				{
								// specifies whether the windowed mode window will be resizable by the user. 
								bool m_Resizable = true;

								// specifies whether the windowed mode window will be initially visible. This hint is ignored for full screen windows
								bool m_Visible = true;

								// specifies whether the windowed mode window will have window decorations such as a border, a close widget, etc. An undecorated window may still allow the user to generate close events on some platforms. This hint is ignored for full screen windows
								bool m_Decorated = true;

								// specifies whether the windowed mode window will be given input focus when created. This hint is ignored for full screen and initially hidden windows
								bool m_Focused = true;

								// specifies whether the full screen window will automatically iconify and restore the previous video mode on input focus loss.This hint is ignored for windowed mode windows
								bool m_AutoIconify = true;

								// specifies whether the windowed mode window will be floating above other regular windows, also called topmost or always-on-top. This is intended primarily for debugging purposes and cannot be used to implement proper full screen windows. This hint is ignored for full screen windows
								bool m_Floating = false;
				};

				struct FramebufferHints
				{
								// specify the desired bit depths of the various components of the default framebuffer; use -1 if there's no preference
								int32 m_RedBits = 8;
								int32 m_GreenBits = 8;
								int32 m_BlueBits = 8;
								int32 m_AlphaBits = 8;
								int32 m_DepthBits = 24;
								int32 m_StencilBits = 8;

								// specifies the desired number of samples to use for multisampling. 0 disables multisampling. -1 means the application has no preference
								int32 m_Samples = 0;

								// specifies whether to use stereoscopic rendering.This is a hard constraint
								bool m_Stereo = false;

								// specifies whether the framebuffer should be sRGB capable
								bool m_SRGBCapable = false;

								// specifies whether the framebuffer should be double buffered.You nearly always want to use double buffering.This is a hard constraint
								bool m_DoubleBuffer = true;
				};

				struct MonitorHints
				{
								// specifies the desired refresh rate for full screen windows. If set to -1, the highest available refresh rate will be used. This hint is ignored for windowed mode windows
								int32 m_RefreshRate = 0;
				};

				class VideoHints
				{
				public:
								VideoHints();
								// to GLFW defaults (notably openGL 1.0!)
								void ResetToDefaults();

								// acquires the current bitsettings and refresh rate for a given monitor (for borderless fullscreen windows)
								void FromVideoMode( const void* _Vidmode );

								// applies the current settings for the next window to be created
								void Apply();

								friend std::ostream& operator << ( std::ostream& _Stream, const VideoHints& _Hints );

								// the following values reflect the defaults from GLFW
								FramebufferHints m_FramebufferHints;
								ContextHints m_ContextHints;
								WindowHints m_WindowHints;
								MonitorHints m_MonitorHints;
				};
}