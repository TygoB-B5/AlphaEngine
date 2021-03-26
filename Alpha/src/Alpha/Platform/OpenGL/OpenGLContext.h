#pragma once

#include "Alpha/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"

namespace Alpha
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* glfwWindow);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}