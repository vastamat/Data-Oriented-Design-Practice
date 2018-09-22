#pragma once

#include <ECS/World.h>

namespace dode
{
				enum class ApplicationState : uint8
				{
								NotRunning,
								Startup,
								Running,
								Transitioning,
								Exitting
				};

				class Application
				{
				public:
								Application();
								~Application();

								Application( const Application& _Other ) = delete;
								Application& operator=( const Application& _Other ) = delete;

								Application( Application&& _Other ) noexcept;
								Application& operator=( Application&& _Other ) noexcept;

								World& CreateNewWorld( const std::string& _WorldName );
								void SetReadyToBeginRunning();

								void Update();
								void BeginTransitionToWorld( std::string& _WorldName );

				protected:
								std::vector<World> m_Worlds;
								int32 m_CurrentWorldId;
								int32 m_NextWorldId;
								ApplicationState m_State;
				};
}

