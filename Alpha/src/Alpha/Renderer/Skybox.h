#pragma once
#include "Alpha/Core.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "PerspectiveCamera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
	class Skybox
	{
	public:
		Skybox();

		void SetCubemap(const Ref<TextureCubemap>& cubemap) { m_Texture = cubemap; };
		void SetSkyboxFollowPositionReference(glm::vec3* position) { m_FollowPosition = position;  RecalculateTransformMatrix();};

		const Ref<TextureCubemap> GetCubemap() const { return m_Texture; }
		const Ref<VertexArray> GetVertexArray() const { return m_VertexArray; }
		const Ref<Shader> GetShader() const { return m_Shader; }
		const glm::mat4 GetTransofrmMatrix() { RecalculateTransformMatrix(); return m_TransformMatrix; }
		void RecalculateTransformMatrix() { m_TransformMatrix = glm::translate(glm::mat4(1.0f), *m_FollowPosition); }

	private:
		glm::vec3*  m_FollowPosition;
		Ref<Shader> m_Shader;
		Ref<TextureCubemap> m_Texture;
		Ref<VertexArray> m_VertexArray;
		glm::mat4 m_TransformMatrix;

		float m_Vertices[24] = {  1.0f, 1.0f, -1.0f,
								 -1.0f, 1.0f, -1.0f,
								 -1.0f, -1.0f, -1.0f,
								  1.0f, -1.0f, -1.0f,
								  1.0f, 1.0f, 1.0f,
								 -1.0f, 1.0f, 1.0f,
								 -1.0f, -1.0f, 1.0f,
								  1.0f, -1.0f, 1.0f };

		uint32_t m_Indices[36] = {
			// front
			0, 1, 2,
			2, 3, 0,
			// right
			1, 5, 6,
			6, 2, 1,
			// back
			7, 6, 5,
			5, 4, 7,
			// left
			4, 0, 3,
			3, 7, 4,
			// bottom
			4, 5, 1,
			1, 0, 4,
			// top
			3, 2, 6,
			6, 7, 3 };
	};
}