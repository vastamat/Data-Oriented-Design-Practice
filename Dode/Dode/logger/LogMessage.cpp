#include "LogMessage.h"

#include "Logger.h"

namespace dode
{
				LogMessage::LogMessage(Logger* _Owner, LogLevel _Level, std::string _File, uint32 _Line)
								: m_Owner(_Owner)
								, m_Meta(_Level, std::move(_File), _Line)
				{
				}

				LogMessage::~LogMessage()
				{
								if (m_Owner)
								{
												m_Owner->Flush(this);
								}
				}

				LogMessage::LogMessage(LogMessage && _Moved)
								: m_Owner(_Moved.m_Owner)
								, m_Meta(std::move(_Moved.m_Meta))
								, m_Buffer(std::move(_Moved.m_Buffer))
				{
								_Moved.m_Owner = nullptr;
				}

				LogMessage & LogMessage::operator=(LogMessage && _Moved)
				{
								m_Owner = _Moved.m_Owner;
								m_Meta = std::move(_Moved.m_Meta);
								m_Buffer = std::move(_Moved.m_Buffer);

								_Moved.m_Owner = nullptr;

								return *this;
				}
}
