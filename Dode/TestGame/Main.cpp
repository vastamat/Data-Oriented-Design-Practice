#include <iostream>

#include <Logger\Logger.h>
#include <Core\Engine.h>

int main()
{
				dode::Logger Logger;
				Logger.AddSink( dode::CreateConsoleSink() );

				dode::Engine Engine;

				Engine.Run();

				std::cin.get();
				return 0;
}