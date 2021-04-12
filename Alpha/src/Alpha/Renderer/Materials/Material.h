#pragma once
#include "../Shader.h"
#include "Alpha/Core.h"

namespace Alpha
{
	class Material
	{
	public:
		virtual const void GetName() = 0;
		virtual const uint32_t GetMaterialID() const = 0;

		virtual const Ref<Shader> GetShader() const = 0;
	};
}