#include "appch.h"
#include "OpenGLTime.h"

#include "glfw/glfw3.h"

namespace Alpha
{
	Time* Time::s_Time = new OpenGLTime();

	void OpenGLTime::TickImpl()
	{
		float newTime = (float)glfwGetTime();

		m_DeltaTime = (newTime - m_OldTime) * m_TimeStep;
		m_ElapsedTime = (float)glfwGetTime() * m_TimeStep;

		m_OldTime = newTime;
	}

	void OpenGLTime::SetTimeStepImpl(float timeStep)
	{
		m_TimeStep = timeStep;
	}
}
