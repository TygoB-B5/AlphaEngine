#pragma once

#include "RendererAPI.h" 

namespace Alpha
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

<<<<<<< HEAD
		inline static void DrawArrays(const Ref<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawArrays(vertexArray);
		}

		inline static void EnableDepthMask(bool enabled)
		{
			s_RendererAPI->EnableDepthMask(enabled);
		}


=======
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
			
	private:
		static RendererAPI* s_RendererAPI;
	};
}