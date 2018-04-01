#include "LogSink.h"

#include <fstream>
#include <iostream>
#include <string>

namespace dode
{
				LogSink CreateConsoleSink()
				{
								auto Func = [](LogMeta _Meta, const std::string& _Message)
								{
												std::cout << _Meta.level << _Message << std::endl;
								};

								return LogSink(std::move(Func));
				}

				LogSink CreateFileSink(const std::string& _Filepath)
				{
								auto Func = [&_Filepath](LogMeta _Meta, std::string _Message)
								{
												std::ofstream file(_Filepath, std::ofstream::out);
											
												file << _Meta.level << _Message << " (" << _Meta.file << ":" << _Meta.line << ")" << std::endl;

												file.close();
								};

								return LogSink(std::move(Func));
				}
}
