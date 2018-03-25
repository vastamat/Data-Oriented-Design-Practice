#include <iostream>
#include <logger\Logger.h>

int main()
{
				dode::Logger Logger;
				Logger.AddSink(dode::CreateConsoleSink());

				LogDebug(Logger) << "Test";
				std::cin.get();
				return 0;
}