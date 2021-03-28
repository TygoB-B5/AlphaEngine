#pragma once
#include "Window.h"
#include "Alpha/LayerStack.h"
#include "Core.h"

#include "Events/Event.h"
#include <Alpha/Events/KeyEvent.h>
#include <Alpha/Events/ApplicationEvent.h>

#include "ImGui/ImGuiLayer.h"

// TEMP
#include "Alpha/Renderer/Shader.h"
#include "Alpha/Renderer/Buffer.h"

namespace Alpha
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application* Get() { return s_Instance; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		bool m_Running = true;
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;


		// TEMP
		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};

	// To be defined in client
	Application* CreateApplication();
}
