#include <catch.hpp>

#include <Time\Timer.h>

SCENARIO("Testing timers", "[Time]")
{
				GIVEN("A timer")
				{
								dode::Timer timer;
								WHEN("The Timer starts and millis passed")
								{
												timer.Start();
												timer.SleepFor(10.0f);

												THEN("Elapsed time for the timer shows around the millis passed")
												{
																float elapsedSeconds = timer.ElapsedMilli();
																REQUIRE(elapsedSeconds >= 10.0f);
																REQUIRE(elapsedSeconds <= 10.5f);
												}
								}
				}
}