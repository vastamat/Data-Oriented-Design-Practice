#pragma once

#include "LogLevel.h"

namespace dode
{
				struct LogMeta
				{
								LogMeta(LogLevel _Level, std::string _File, uint32_t _Line);

								LogLevel level;
								std::string file;
								uint32_t line;
				};

				std::ostream& operator << (std::ostream& _OStream, const dode::LogMeta& _Level);
}
