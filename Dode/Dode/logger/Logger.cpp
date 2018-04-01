#include "Logger.h"

namespace dode
{
				void Logger::AddSink(LogSink _Sink)
				{
								m_LogSinks.emplace_back(std::move(_Sink));
				}

				void Logger::RemoveAllSinks()
				{
								m_LogSinks.clear();
				}

				LogMessage Logger::CreateMessage(LogLevel _Level, std::string _File, uint32 _Line)
				{
								return LogMessage(this, _Level, std::move(_File), _Line);
				}

				void Logger::Flush(const LogMessage * _Message)
				{
								LogMeta Meta = _Message->GetMeta();
								std::string Msg = _Message->GetMessage();

								for (const auto& Sink : m_LogSinks)
								{
												Sink.Write(Meta, Msg);
								}
				}
}
