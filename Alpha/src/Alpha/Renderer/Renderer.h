#pragma once
#include "RenderCommand.h"
#include "OrtographicCamera.h"
#include "PerspectiveCamera.h"

#include "Alpha/Objects/GameObject.h"


#include "Shader.h"

namespace Alpha
{
	class Renderer
	{
	public:
		static void BeginScene(OrtographicCamera& camera); // Params
		static void BeginScene(PerspectiveCamera& camera); // Params

		static void EndScene();
		static void Init();

<<<<<<< HEAD
		static void Submit(const Ref<GameObject>& gameObject);
=======
		static void Submit(const Ref<Shader> shader, const Ref<VertexArray> vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
>>>>>>> 8ea3c0db814c87be0651558710da73bd88f2458c

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}