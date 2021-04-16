#pragma once
#include "glfw/glfw3.h"

#include "Alpha/Time.h"

namespace Alpha
{
	class OpenGLTime : public Time
	{
	public:
		OpenGLTime() : m_TimeStep(1), m_DeltaTime(0), m_OldTime(0), m_ElapsedTime(0), m_Fps(0), m_Frames(0), m_NextUpdate(0) {}

		virtual float GetDeltaTimeImpl() const override { return m_DeltaTime; }
		virtual float GetElapsedTimeImpl() const override { return m_ElapsedTime; }
		virtual float GetElapsedRealTimeImpl() const override { return (float)glfwGetTime(); }
		virtual uint32_t GetFpsImpl() const override { return m_Fps; }
		virtual void SetTimeStepImpl(float timeStep) override { m_TimeStep = timeStep; }

		virtual void TickImpl() override;

	private:
		float m_TimeStep;
		float m_ElapsedTime;
		float m_DeltaTime;

		float m_OldTime;

		float m_FpsUpdateRate = 5;
		float m_NextUpdate;
		uint32_t m_Fps;
		uint32_t m_Frames;
	};
}