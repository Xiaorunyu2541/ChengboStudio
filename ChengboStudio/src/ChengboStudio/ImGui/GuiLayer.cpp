#include "pch.h"
#include "GuiLayer.h"
#include "Application.h"
#include "imgui_impl_glfw.h"
#include "Platform/Windows/WindowsImpl.h"

#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

namespace ChengboStudio 
{
	GuiLayer::GuiLayer()
		: Layer("ImGui")
	{
		
	}

	GuiLayer::~GuiLayer()
	{
	
	}

	void GuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		Application* app = &Application::GetInstace();
		
		GLFWwindow* window = static_cast<GLFWwindow*>(app->GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void GuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GuiLayer::OnUpdate()
	{
		
		Window& window = Application::GetInstace().GetWindow();

		ImGuiIO& io = ImGui::GetIO();

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		io.DisplaySize = ImVec2((float)window.GetWidth(), (float)window.GetHeight());

		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	bool GuiLayer::OnWindowResize(EvtWindowResize& evt)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)evt.GetWidth(), (float)evt.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, evt.GetWidth(), evt.GetHeight());

		return false;
	}

	void GuiLayer::OnEvent(Event& evt)
	{
		Dispatcher dispatcher(evt);
		dispatcher.Dispatch<EvtWindowResize>(BIND_EVENT_FN(GuiLayer::OnWindowResize));
	}
}