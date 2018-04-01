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
