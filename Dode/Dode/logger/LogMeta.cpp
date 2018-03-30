#include "LogMeta.h"

#include <string>

namespace dode
{
				LogMeta::LogMeta(LogLevel _Level, std::string _File, uint32_t _Line)
								: level(_Level)
								, file(std::move(_File))
								, line(_Line)
				{
				}

				std::ostream & operator<<(std::ostream & _OStream, const LogMeta & _Meta)
				{
								_OStream << "(" << _Meta.file << ":" << _Meta.line << ") " << _Meta.level;
								return _OStream;
				}
}
