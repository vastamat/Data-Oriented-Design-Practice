#include <catch.hpp>

#include <Logger\Logger.h>

SCENARIO( "Logging to a log sink", "[Logger]" )
{
				GIVEN( "A logger with a log sink which writes the incoming message to a string stream" )
				{
								std::stringstream message;
								dode::LogSink StringStreamSink( [ &message ]( dode::LogMeta _Meta, const std::string& _Message )
								{
												message << _Message;
								} );

								dode::Logger Logger;
								Logger.AddSink( StringStreamSink );

								WHEN( "A message is logged" )
								{
												std::string loggedMessage = "Test Test 123\n";
												DLOG_DEBUG( Logger ) << loggedMessage;

												THEN( "The logged message is added to the string stream" )
												{
																REQUIRE( message.str() == loggedMessage );
												}
								}

								WHEN( "Multiple messages are logged" )
								{
												std::string loggedMessage1 = "Test Test 123\n";
												std::string loggedMessage2 = "Descriptive message\t";
												std::string loggedMessage3 = "Come on!";

												std::string AllMessages = loggedMessage1 + loggedMessage2 + loggedMessage3;

												DLOG_DEBUG( Logger ) << loggedMessage1;
												DLOG_DEBUG( Logger ) << loggedMessage2;
												DLOG_DEBUG( Logger ) << loggedMessage3;

												THEN( "The logged messages are added to the string stream" )
												{
																REQUIRE( message.str() == AllMessages );
												}
								}
				}
}