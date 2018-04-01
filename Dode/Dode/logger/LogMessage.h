#pragma once

#include "LogMeta.h"

#include <ostream>
#include <sstream>

namespace dode
{
				class Logger;

				class LogMessage
				{
				public:
								LogMessage(Logger* _Owner, LogLevel _Level, std::string _File, uint32 _Line);
								~LogMessage();

								LogMessage(const LogMessage& _Copy) = delete;
								LogMessage(LogMessage&& _Moved);

								LogMessage& operator=(const LogMessage& _Copy) = delete;
								LogMessage& operator=(LogMessage&& _Moved);

								template <typename T>
								LogMessage& operator<< (const T& _Value)
								{
												m_Buffer << _Value;
												return *this;
								}

								inline LogMessage& operator<< (std::ostream& (*_IostreamFunc)(std::ostream&)) // accept iostream manipulator functions (endl etc)
								{
												_IostreamFunc(m_Buffer);
												return *this;
								}

								inline std::string GetMessage() const { return m_Buffer.str(); }

								inline LogMeta GetMeta() const noexcept { return m_Meta; }

				private:
								std::ostringstream m_Buffer;

								LogMeta m_Meta;

								Logger* m_Owner;
				};
}
