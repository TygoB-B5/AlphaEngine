#pragma once
#include "RenderCommand.h"
#include "OrtographicCamera.h"
#include "PerspectiveCamera.h"

#include "Alpha/Objects/GameObject.h"
#include "Shader.h"
#include "Skybox.h"
#include "Materials/Material.h"
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

		static void SubmitSkybox();
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Material>& material, const glm::mat4& transform);
		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

		static auto* GetSceneData() { return Renderer::m_SceneData; }

		static void SetSkybox(const Ref<Skybox>& skybox) { m_SceneData->Skybox = skybox; }
		static const Ref<Skybox> GetSkybox() { return m_SceneData->Skybox; }

		static void AddLight(const Ref<DirectionalLight>& light) { m_SceneData->DirectionalLights.push_back(light); }
		static Ref<DirectionalLight> GetLight(int index) { return m_SceneData->DirectionalLights[index]; }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
			glm::mat4 ViewMatrix;
			std::vector<Ref<DirectionalLight>> DirectionalLights;
			Ref<Skybox> Skybox;
			glm::vec3 CameraPosition;
		};
		static SceneData* m_SceneData;
	};
}