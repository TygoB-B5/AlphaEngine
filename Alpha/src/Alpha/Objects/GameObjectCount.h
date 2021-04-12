#pragma once

namespace Alpha
{
	class GameObjectCount
	{
	public:
		static uint32_t GetNewObjectID() { return s_ObjectID; s_ObjectID++; }

	private:
		static uint32_t s_ObjectID;
	};
}