#pragma once

#include "LogMeta.h"

#include <functional>

namespace dode
{
				using WriteFunc = std::function<void(LogMeta _Meta, const std::string& _Message)>;

				class LogSink
				{
				public:
								LogSink(WriteFunc _Func);

								void Write(LogMeta _Meta, const std::string& _Message) const;

				private:
								WriteFunc m_WriteFunc;
				};

				LogSink CreateConsoleSink();
				LogSink CreateFileSink(const std::string& _Filepath);
}
