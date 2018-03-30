#include "LogLevel.h"

namespace dode
{
				std::ostream & operator<<(std::ostream & _Ostream, const LogLevel & _Level)
				{
								switch (_Level)
								{
								case LogLevel::Debug: _Ostream << "Debug: "; break;
								case LogLevel::Warning: _Ostream << "Warning: "; break;
								case LogLevel::Error: _Ostream << "Error: "; break;
								default:	_Ostream << "Unknown Log Level: "; break;
								}
								return _Ostream;
				}
}
