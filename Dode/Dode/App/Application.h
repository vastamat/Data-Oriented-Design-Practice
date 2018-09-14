#pragma once

namespace dode
{
				class Application
				{
				public:
								Application();
								virtual ~Application();

								virtual void AddWorlds();

								void UpdateCurrentWorld();

				};
}

