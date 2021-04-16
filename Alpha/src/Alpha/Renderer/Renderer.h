#pragma once
#include "RenderCommand.h"
#include "OrtographicCamera.h"
#include "PerspectiveCamera.h"

#include "Alpha/Objects/GameObject.h"
#include "Shader.h"
#include "Skybox.h"
#include "DirectionalLight.h"

namespace Alpha
{
	class Renderer
	{
	public:
		static void BeginScene(PerspectiveCamera& camera); // Params
		static void BeginScene(OrtographicCamera& camera); // Params

		static void EndScene();
		static void Init();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform, const DirectionalLight& light, const glm::vec3& camPos);
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::mat4 ViewMatrix;
		};

		static SceneData* m_SceneData;
	};
}