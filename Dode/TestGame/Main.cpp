#include <iostream>

#include <Logger\Logger.h>

int main()
{
				dode::Logger Logger;
				Logger.AddSink(dode::CreateConsoleSink());

				DLOG_DEBUG(Logger) << "Test";
				std::cin.get();
				return 0;
}