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


		float verticies[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> triangleVertexBuffer;
		triangleVertexBuffer.reset(VertexBuffer::Create(verticies, sizeof(verticies)));
		triangleVertexBuffer->SetLayout(
			{
				{ShaderDataType::Float3, "a_Position" },
				{ShaderDataType::Float4, "a_Color" }
			});

		triangleVertexBuffer->Bind();

		unsigned int indicis[3] = { 0, 1, 2 };

		std::shared_ptr<IndexBuffer> triangleIndexBuffer;
		triangleIndexBuffer.reset(IndexBuffer::Create(indicis, sizeof(indicis) / sizeof(unsigned int)));
		triangleIndexBuffer->Bind();

		std::string vertexSrc = R"(
		#version 330 core
	
		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
	
		out vec3 v_Position;	
		out vec4 v_Color;	

		void main()
		{
			v_Color = a_Color;
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

		std::string fragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 o_Color;		
		in vec4 v_Color;

		void main()
		{
			o_Color = v_Color;
		}
	)";

		m_Shader.reset(Shader::Create(vertexSrc, fragmentSrc));
		m_Shader->Bind();

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(triangleVertexBuffer);
		m_VertexArray->SetIndexBuffer(triangleIndexBuffer);


		float squareVerticies[3 * 4] =
		{
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			1.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(VertexBuffer::Create(squareVerticies, sizeof(squareVerticies)));
		squareVertexBuffer->SetLayout(
			{
				{ShaderDataType::Float3, "a_Position" }
			});

		squareVertexBuffer->Bind();

		unsigned int squareIndicis[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer.reset(IndexBuffer::Create(squareIndicis, sizeof(squareIndicis) / sizeof(unsigned int)));
		squareIndexBuffer->Bind();

		std::string squareVertexSrc = R"(
		#version 330 core
	
		layout(location = 0) in vec3 a_Position;
	
		out vec3 v_Position;	

		void main()
		{
			v_Position = a_Position;
			gl_Position = vec4(a_Position, 1.0);
		}
	)";

		std::string squareFragmentSrc = R"(
		#version 330 core

		layout(location = 0) out vec4 o_Color;		
		
		in vec3 v_Position;
		
		void main()
		{
			o_Color = vec4(v_Position * 0.75 + 1, 1.0);
		}
	)";

		m_SquareShader.reset(Shader::Create(squareVertexSrc, squareFragmentSrc));
		m_SquareShader->Bind();

		m_SquareVertexArray.reset(VertexArray::Create());
		m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
		m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);
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

			m_SquareShader->Bind();
			m_SquareVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexbuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexbuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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
