#include "LogMessage.h"

#include "Logger.h"

namespace dode
{
				LogMessage::LogMessage(Logger* _owner, LogLevel _level, std::string _file, uint32_t _line)
								: m_Owner(_owner)
								, m_Meta(_level, std::move(_file), _line)
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

				LogMessage & LogMessage::operator<<(std::ostream &(*_iostreamFunc)(std::ostream &))
				{
								_iostreamFunc(m_Buffer);
								return *this;
				}
				std::string LogMessage::GetMessage() const
				{
								return m_Buffer.str();
				}
				LogMeta LogMessage::GetMeta() const noexcept
				{
								return m_Meta;
				}
}
