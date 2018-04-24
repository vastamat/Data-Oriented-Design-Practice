#include "LogMeta.h"

#include <string>

namespace dode
{
				LogMeta::LogMeta(LogLevel _Level, std::string _File, uint32 _Line)
								: m_Level(_Level)
								, m_File(std::move(_File))
								, m_Line(_Line)
				{
				}

				std::ostream & operator<<(std::ostream & _OStream, const LogMeta & _Meta)
				{
								_OStream << "(" << _Meta.m_File << ":" << _Meta.m_Line << ") " << _Meta.m_Level;
								return _OStream;
				}
}
