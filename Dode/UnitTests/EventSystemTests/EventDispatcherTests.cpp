#include <catch.hpp>

#include <EventSystem\EventDispatcher.h>

struct TestEvent 
{
				const std::string TestMessage;
};

struct TestEventListener
{
				TestEventListener()
				{
								dode::EventDispatcher::AddListener<TestEvent>(this);
				}

				~TestEventListener()
				{
								dode::EventDispatcher::RemoveListener<TestEvent>(this);
				}

				void OnEvent(const TestEvent& _Event)
				{
								TestMessage = _Event.TestMessage;
								timesCalled++;
				}

				std::string TestMessage;
				uint8_t timesCalled = 0u;
};

SCENARIO("Register a listener and dispatch an event", "[EventSystem]")
{
				GIVEN("An event listener that is registered to the dispatcher to listen for a given event")
				{
								TestEventListener TEL;
								WHEN("An event of that type is broadcasted")
								{
												std::string EventMessage = "Event Was Called";
												dode::EventDispatcher::BroadcastEvent<TestEvent>(TestEvent{ EventMessage });

												THEN("The event listener's callback function is called with that event param")
												{
																REQUIRE(TEL.TestMessage == EventMessage);
																REQUIRE(TEL.timesCalled == 1u);
												}
								}
				}
}