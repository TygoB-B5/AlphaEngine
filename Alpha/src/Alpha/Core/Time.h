#pragma once

namespace Alpha
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time)
		{}

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.0f; }

		operator float() const { return m_Time; }

	private:
		float m_Time;
	};

	class Time
	{
	public:
		static void Init();

		static float GetDeltaTime() { return s_Time->GetDeltaTimeImpl(); }
		static float GetElapsedTime() { return s_Time->GetElapsedTimeImpl(); }
		static float GetElapsedRealTime() { return s_Time->GetElapsedRealTimeImpl(); }
		static float GetFps() { return s_Time->GetFpsImpl(); }

		static void Tick(){ s_Time->TickImpl(); }

		static void SetTimeStep(float timeStep) { return s_Time->SetTimeStepImpl(timeStep); }

	private:
		virtual void TickImpl() = 0;
		virtual float GetDeltaTimeImpl() const = 0;
		virtual float GetElapsedTimeImpl() const = 0;
		virtual float GetElapsedRealTimeImpl() const = 0;
		virtual float GetFpsImpl() const = 0;

		virtual void SetTimeStepImpl(float timeStep) = 0;

	private:
		static Time* s_Time;
	};
}