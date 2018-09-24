#include <iostream>

#include <Core\Engine.h>
#include <Logger\Logger.h>
#include <TaskManager/ThreadPool.h>
#include <ECS/Component.h>

struct TestComponent : public dode::Component
{
				dode::uint64 EightBytes = 0;
				dode::uint32 FourBytes = 0;
				dode::uint16 TwoBytes = 0;
				dode::uint8 OneByte = 0;
};

class TestSystem : public dode::System
{
public:
				TestSystem()
				{
								m_SystemSignature.set( dode::GetIdOfComponentType<TestComponent>() );

								m_TestLogger.AddSink( dode::CreateConsoleSink() );
				}
				~TestSystem()
				{
				}

				virtual void Initialize() override
				{
								DLOG_DEBUG( m_TestLogger ) << "Initializing Test System";
				}
				virtual void Uninitialize() override
				{
								DLOG_DEBUG( m_TestLogger ) << "Uninitializing Test System";
				}
				virtual void Update( dode::World& _World, float _Dt ) override
				{
								DLOG_DEBUG( m_TestLogger ) << "Updating Test System - Number of Registered Entities: " << m_RegisteredEntities.size();

								for ( size_t i = 0; i < m_RegisteredEntities.size(); i++ )
								{
												DLOG_DEBUG( m_TestLogger ) << "Updating Test System's Entity # " << m_RegisteredEntities[i].m_Id;
								}
				}

private:

				dode::Logger m_TestLogger;
};

dode::Application MakeTestApp()
{
				dode::Application testApp;
				dode::World& testWorld = testApp.CreateNewWorld( "World_1" );

				testWorld.AddSystem( std::make_unique<TestSystem>() );

				dode::Entity entity = testWorld.CreateEntity();

				testWorld.AddComponent<TestComponent>( entity, TestComponent{} );

				return testApp;
}
int main()
{
				dode::Logger Logger;
				Logger.AddSink( dode::CreateConsoleSink() );

				dode::Engine Engine;
				Engine.SetApplication( MakeTestApp() );
				Engine.Run();
				
				/*std::vector<dode::World> worlds;
				dode::World testWorld("test");
				worlds.emplace_back( "Test2" );
				auto& world2 = worlds.back();*/

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