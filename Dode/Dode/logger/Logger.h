#pragma once

#include "LogSink.h"
#include "LogMessage.h"

#include <vector>

namespace dode
{
				class Logger
				{
				public:
								void AddSink(LogSink _Sink);
								void RemoveAllSinks();

								LogMessage CreateMessage(LogLevel _Level, std::string _File, uint32_t _Line);

								void Flush(const LogMessage* _Message);

				private:
								std::vector<LogSink> m_LogSinks;
				};

}

#define LogDebug(Logger) Logger.CreateMessage(dode::LogLevel::Debug, __FILE__, __LINE__)
#define LogWarning(Logger) Logger.CreateMessage(dode::LogLevel::Warning, __FILE__, __LINE__)
#define LogError(Logger)   Logger.CreateMessage(dode::LogLevel::Error, __FILE__, __LINE__)