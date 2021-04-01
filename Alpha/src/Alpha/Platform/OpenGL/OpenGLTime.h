#pragma once
#include "glfw/glfw3.h"

#include "Alpha/Time.h"

namespace Alpha
{
	class OpenGLTime : public Time
	{
	public:
		OpenGLTime() : m_TimeStep(1), m_DeltaTime(0), m_OldTime(0), m_ElapsedTime(0) {}

		virtual float GetDeltaTimeImpl() const override { return m_DeltaTime; }
		virtual float GetElapsedTimeImpl() const override { return m_ElapsedTime; }
		virtual float GetElapsedRealTimeImpl() const override { return (float)glfwGetTime(); }

		virtual void TickImpl() override;

		virtual void SetTimeStepImpl(float timeStep) override;

	private:
		float m_DeltaTime;
		float m_ElapsedTime;
		float m_TimeStep;
		float m_OldTime;
	};
}