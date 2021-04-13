#pragma once

namespace Alpha
{
	class GameObjectCount
	{
	public:
		GameObjectCount()
		{ m_CurrentID = ++s_ObjectID; }

		static uint32_t GetNewObjectID() { return s_ObjectID;}

	private:
		uint32_t m_CurrentID;

		static uint32_t s_ObjectID;
	};
}