#include <catch.hpp>

#include <EventSystem\EventDispatcher.h>

struct TestEvent 
{
				const std::string TestMessage;
};

struct TestEventListener
{
				void BeginListening()
				{
								dode::EventDispatcher::AddListener<TestEvent>(this);
				}

				void StopListening()
				{
								dode::EventDispatcher::RemoveListener<TestEvent>(this);
				}

				void OnEvent(const TestEvent& _Event)
				{
								TestMessage = _Event.TestMessage;
								timesCalled++;
				}

				std::string TestMessage;
				dode::uint8 timesCalled = 0u;
};

SCENARIO("Register a listener and dispatch an event", "[EventSystem]")
{
				GIVEN("A Test event listener")
				{
								TestEventListener TEL;
								WHEN("It begins listening and an event of that type is broadcasted")
								{
												TEL.BeginListening();
												std::string EventMessage = "Event Was Called";
												dode::EventDispatcher::BroadcastEvent<TestEvent>(TestEvent{ EventMessage });
												TEL.StopListening();

												THEN("The event listener's callback function is called with that event param")
												{
																REQUIRE(TEL.TestMessage == EventMessage);
																REQUIRE(TEL.timesCalled == 1u);
												}
								}

								WHEN("It begins listening and later stops before an event is broadcasted")
								{
												TEL.BeginListening();
												std::string EventMessage = "Event Was Called";
												TEL.StopListening();
												dode::EventDispatcher::BroadcastEvent<TestEvent>(TestEvent{ EventMessage });

												THEN("The event is not received")
												{
																REQUIRE(TEL.TestMessage == "");
																REQUIRE(TEL.timesCalled == 0u);
												}
								}
				}
}