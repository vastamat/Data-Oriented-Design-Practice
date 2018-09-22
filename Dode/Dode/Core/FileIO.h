#pragma once

#include <string>

#include <Json/json.hpp>

namespace dode
{
				namespace FileIO
				{
								bool ReadFileToBuffer( const std::string& _filePath, std::string& _buffer );

								bool WriteBufferToFile( const std::string& _buffer, const std::string& _filePath );

								bool WriteJsonObjectToFile( const nlohmann::json& _obj, const std::string& _filePath );

								bool ReadFileToJsonObject( nlohmann::json& _obj, const std::string& _filePath );

								void CreateFilepath( const std::string& _filepath );
				}
}