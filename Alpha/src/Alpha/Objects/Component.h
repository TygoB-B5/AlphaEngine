#pragma once

namespace Alpha
{
	class Component
	{
	public:
		virtual std::string GetTypeName() const = 0;
	};
}