#pragma once

#include "Core/CommonIncludes.h"

#include <ostream>

namespace dode
{
				enum class LogLevel : uint8
				{
								Debug,
								Warning,
								Error
				};

				std::ostream& operator << (std::ostream& _OStream, const dode::LogLevel& _Level);
}

