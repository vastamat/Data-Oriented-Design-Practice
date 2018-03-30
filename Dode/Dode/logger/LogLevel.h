#pragma once

#include <ostream>
#include <cstdint>

namespace dode
{
				enum class LogLevel : uint8_t
				{
								Debug,
								Warning,
								Error
				};

				std::ostream& operator << (std::ostream& _OStream, const dode::LogLevel& _Level);
}

