#include "FileIO.h"
#include "CommonIncludes.h"

#include <fstream>
#include <filesystem>
#include <iomanip>

namespace dode
{
				namespace FileIO
				{
								bool ReadFileToBuffer( const std::string & _filePath, std::string & _buffer )
								{
												std::ifstream file( _filePath, std::ios::binary );
												if ( file.fail() )
												{
																perror( _filePath.c_str() );
																return false;
												}

												//seek to the end
												file.seekg( 0, std::ios::end );

												//Get the file size
												uint32 fileSize = ( uint32 )file.tellg();
												file.seekg( 0, std::ios::beg );

												//Reduce the file size by any header bytes that might be present
												fileSize -= ( uint32 )file.tellg();

												//resize the buffer to the exact size we need it
												_buffer.resize( fileSize );

												//read the file to the buffer
												file.read( &_buffer.front(), fileSize );

												//close the file
												file.close();

												return true;
								}

								bool WriteBufferToFile( const std::string & _buffer, const std::string & _filePath )
								{
												std::ofstream file( _filePath, std::ios::out | std::ios::app );
												if ( file.fail() )
												{
																CreateFilepath( _filePath.c_str() );

																file = std::ofstream( _filePath, std::ios::out | std::ios::app );
																if ( file.fail() )
																{
																				perror( _filePath.c_str() );
																				return false;
																}
												}

												file << _buffer;

												file.close();

												return true;
								}

								bool WriteJsonObjectToFile( const nlohmann::json& _obj, const std::string & _filePath )
								{
												std::ofstream file( _filePath, std::ios::out | std::ios::app );

												if ( file.fail() )
												{
																CreateFilepath( _filePath.c_str() );

																file = std::ofstream( _filePath, std::ios::out | std::ios::app );
																if ( file.fail() )
																{
																				perror( _filePath.c_str() );
																				return false;
																}
												}

												file << std::setw( 4 ) << _obj;

												file.close();

												return true;
								}

								void CreateFilepath( const std::string & _filePath )
								{
												namespace fs = std::experimental::filesystem;

												uint32 countToNextSlash = _filePath.find_first_of( '/' );

												while ( countToNextSlash != std::string::npos )
												{
																std::string directory = _filePath.substr( 0, countToNextSlash );

																if ( !fs::exists( directory ) )
																{
																				fs::create_directory( directory );
																}

																countToNextSlash = _filePath.find( '/', countToNextSlash + 1 );
												}
								}
				}
}