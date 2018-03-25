#include "LogLevel.h"

namespace dode
{
				std::ostream & operator<<(std::ostream & _os, const LogLevel & _level)
				{
								switch (_level)
								{
								case LogLevel::Debug: _os << "Debug: "; break;
								case LogLevel::Warning: _os << "Warning: "; break;
								case LogLevel::Error: _os << "Error: "; break;
								default:	_os << "Unknown Log Level: "; break;
								}
								return _os;
				}
}
