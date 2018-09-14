#include "TestClass.h"

#include <ECS/Component.h>
#include <Logger\Logger.h>

struct FloatMember : dode::Component
{
				float m_Member;
};

struct DoubleMember : dode::Component
{
				double m_Member;
};

void LogComponents()
{
				dode::Logger Logger;
				Logger.AddSink( dode::CreateConsoleSink() );

				dode::uint32 TestComponentId1 = dode::GetIdOfComponentType<FloatMember>();
				dode::uint32 TestComponentId2 = dode::GetIdOfComponentType<DoubleMember>();
				dode::uint32 TestComponentId11 = dode::GetIdOfComponentType<FloatMember>();
				dode::uint32 TestComponentId21 = dode::GetIdOfComponentType<DoubleMember>();

				DLOG_DEBUG( Logger ) << TestComponentId1 << std::endl;
				DLOG_DEBUG( Logger ) << TestComponentId2 << std::endl;
				DLOG_DEBUG( Logger ) << TestComponentId11 << std::endl;
				DLOG_DEBUG( Logger ) << TestComponentId21 << std::endl;
}
