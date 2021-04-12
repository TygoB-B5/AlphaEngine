#include "appch.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"

namespace Alpha
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexbuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawArrays(const Ref<VertexArray>& vertexArray)
	{
		GLint size = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		glDrawArrays(GL_TRIANGLES, 0, size / sizeof(float));

	}

	void OpenGLRendererAPI::EnableDepthMask(bool enabled)
	{
		GLboolean enable = GL_FALSE;

		if (enabled)
			enable = GL_TRUE;

		glDepthMask(enable);
	}
}