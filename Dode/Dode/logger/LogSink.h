#pragma once

#include "LogMeta.h"

#include <functional>

namespace dode
{
				using WriteFunc = std::function<void(LogMeta _Meta, const std::string& _Message)>;

				class LogSink
				{
				public:
								LogSink(WriteFunc _Func)
												: m_WriteFunc(std::move(_Func))
								{ }

								inline void Write(LogMeta _Meta, const std::string& _Message) const { m_WriteFunc(_Meta, _Message); }

				private:
								WriteFunc m_WriteFunc;
				};

				LogSink CreateConsoleSink();
				LogSink CreateFileSink(const std::string& _Filepath);
}
