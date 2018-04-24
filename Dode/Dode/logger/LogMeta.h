#pragma once

#include "LogLevel.h"

namespace dode
{
				struct LogMeta
				{
								LogMeta(LogLevel _Level, std::string _File, uint32 _Line);

								LogLevel m_Level;
								std::string m_File;
								uint32 m_Line;
				};

				std::ostream& operator << (std::ostream& _OStream, const dode::LogMeta& _Level);
}
