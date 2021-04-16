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
		virtual void DrawArrays(const Ref<VertexArray>& vertexArray) override;

		virtual void EnableDepthMask(bool enabled) override;
		virtual void SetCullingType(int type) override;

	};
}