#include "appch.h"
#include "OpenGLTime.h"

#include "glfw/glfw3.h"

namespace Alpha
{
	Time* Time::s_Time = new OpenGLTime();

	void OpenGLTime::TickImpl()
	{
		// Update Times
		float newTime = (float)glfwGetTime();
		m_DeltaTime = (newTime - m_OldTime) * m_TimeStep;
		m_ElapsedTime = (float)glfwGetTime() * m_TimeStep;
		m_OldTime = newTime;

		// Update Fps
		m_Frames++;
		if (newTime > m_NextUpdate)
		{
			m_NextUpdate += 1.0f / m_FpsUpdateRate;
			m_Fps = (uint32_t)(m_Frames * m_FpsUpdateRate);
			m_Frames = 0;
		}
	}
}
