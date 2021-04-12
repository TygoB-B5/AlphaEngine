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

		static void Submit(const Ref<GameObject>& gameObject);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}