#include "appch.h"
#include "Application.h"

#include "glad/glad.h"

#include "Input.h"

namespace Alpha
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AP_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(AP_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float verticies[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		std::string vertexSrc = R"(
		#version 330 core
	
		layout(location = 0) in vec3 a_Position;
	
		out vec3 v_Position;		

		void main()
		{
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

		std::string fragmentSrc = R"(
		#version 330 core
		
		in vec3 v_Position;		

		layout(location = 0) out vec4 o_Color;

		void main()
		{
			o_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
		}
	)";

		unsigned int indicis[3] = { 0, 1, 2 };

		m_VertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		m_VertexBuffer->Bind();

		m_IndexBuffer.reset(IndexBuffer::Create(indicis, 3));
		m_IndexBuffer->Bind();

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, m_IndexBuffer->GetCount(), GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		m_Shader->Bind();
	}

	Application::~Application()
	{
		m_Window.reset();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(AP_BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.GetHandled())
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.15f, 0.15f, 0.15f, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}
