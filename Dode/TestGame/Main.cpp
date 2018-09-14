#include <iostream>

#include <Core\Engine.h>
#include <Logger\Logger.h>
#include <TaskManager/ThreadPool.h>
#include <ECS/Component.h>

#include "TestClass.h"

struct TestComponent : public dode::Component
{
				dode::uint64 EightBytes;
				dode::uint32 FourBytes;
				dode::uint16 TwoBytes;
				dode::uint8 OneByte;
};

struct TestComponent2 : public dode::Component
{
				dode::uint64 EightBytes;
				dode::uint32 FourBytes;
				dode::uint16 TwoBytes;
				dode::uint8 OneByte;
};

int main()
{
				dode::Logger Logger;
				Logger.AddSink( dode::CreateConsoleSink() );
				//dode::uint32 TestComponentId1 = dode::GetIdOfComponentType<TestComponent>();
				//dode::uint32 TestComponentId2 = dode::GetIdOfComponentType<TestComponent2>();
				//dode::uint32 TestComponentId11 = dode::GetIdOfComponentType<TestComponent>();
				//dode::uint32 TestComponentId21 = dode::GetIdOfComponentType<TestComponent2>();

				//DLOG_DEBUG( Logger ) << TestComponentId1 << std::endl;
				//DLOG_DEBUG( Logger ) << TestComponentId2 << std::endl;
				//DLOG_DEBUG( Logger ) << TestComponentId11 << std::endl;
				//DLOG_DEBUG( Logger ) << TestComponentId21 << std::endl;
				//LogComponents();
				dode::Engine Engine;

				Engine.Run();

				//dode::ThreadPool pool;

				//for ( size_t i = 0; i <= std::thread::hardware_concurrency(); ++i )
				//{
				//				auto result = pool.Enqueue( []
				//				{
				//								size_t counter = 0;
				//								while ( counter != 10 )
				//								{
				//												std::cout << "Thread Id: " << std::this_thread::get_id() << " counter = " << counter << std::endl;
				//												counter++;
				//								}

				//								return counter;
				//				} );

				//				/*std::cout << "Before checking result validity" << std::endl;
				//				if ( auto countedResult = result.get() )
				//				{
				//								std::cout << "Thread Id: " << std::this_thread::get_id() << " result = " << countedResult << std::endl;
				//								assert( countedResult == 10 );
				//				}*/
				//}



				std::cin.get();
				return 0;
}