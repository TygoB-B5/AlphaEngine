#pragma once
#include "Alpha/Renderer/RendererAPI.h"

namespace Alpha
{
	class OpenGLRendererAPI : public RendererAPI
	{
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void Init() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
<<<<<<< HEAD
		virtual void DrawArrays(const Ref<VertexArray>& vertexArray) override;

		virtual void EnableDepthMask(bool enabled) override;

=======
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
	};
}