#pragma once
#include "RenderCommand.h"

namespace Alpha
{
	class Renderer
	{
	public:
		static void BeginScene(); // Params
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray> vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}