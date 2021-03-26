#include "appch.h"
#include "OpenGLContext.h"
#include "glad/glad.h"

namespace Alpha
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		AP_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AP_CORE_ASSERT(status, "Failed to initialize Glad!");

		AP_CORE_INFO("OpenGL Info:");
		AP_CORE_INFO("	Vendor: {0}",	  glGetString(GL_VENDOR));
		AP_CORE_INFO("	Renderer: {0}", glGetString(GL_RENDERER));
		AP_CORE_INFO("	Version: {0}",  glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glBegin(GL_TRIANGLES);
		glEnd();

		glfwSwapBuffers(m_WindowHandle);
	}
}