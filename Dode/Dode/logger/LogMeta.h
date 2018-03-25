#pragma once

#include "LogLevel.h"

namespace dode
{
				struct LogMeta
				{
								LogMeta(LogLevel _level, std::string _file, uint32_t _line);

								LogLevel level;
								std::string file;
								uint32_t line;
				};

				std::ostream& operator << (std::ostream& _os, const dode::LogMeta& _level);
}
