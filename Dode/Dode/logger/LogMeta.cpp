#include "LogMeta.h"

#include <string>

namespace dode
{
				LogMeta::LogMeta(LogLevel _level, std::string _file, uint32_t _line)
								: level(_level)
								, file(std::move(_file))
								, line(_line)
				{
				}

				std::ostream & operator<<(std::ostream & _Stream, const LogMeta & _Meta)
				{
								_Stream << "(" << _Meta.file << ":" << _Meta.line << ") " << _Meta.level;
								return _Stream;
				}
}
