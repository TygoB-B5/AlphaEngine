#pragma once
#include "OrtographicCamera.h"
#include "Shader.h"
#include "Texture.h"

namespace Alpha
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();
		static void BeginScene(const OrtographicCamera& camera); // Params
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture);
	};
}