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

								inline LogMessage CreateMessage(LogLevel _Level, std::string _File, uint32 _Line)
								{
												return LogMessage(this, _Level, std::move(_File), _Line);
								}

								void Flush(const LogMessage* _Message);

				private:
								std::vector<LogSink> m_LogSinks;
				};

}

#define DLOG_DEBUG(Logger) Logger.CreateMessage(dode::LogLevel::Debug, __FILE__, __LINE__)
#define DLOG_WARNING(Logger) Logger.CreateMessage(dode::LogLevel::Warning, __FILE__, __LINE__)
#define DLOG_ERROR(Logger)   Logger.CreateMessage(dode::LogLevel::Error, __FILE__, __LINE__)