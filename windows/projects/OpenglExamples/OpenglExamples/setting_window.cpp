#include "setting_window.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <vector>
#include <memory>
#include "render.h"

extern std::vector<std::shared_ptr<Render>> all_reanders;
extern std::shared_ptr<Render> using_render;
#define HIDE_LABEL ("##" + std::to_string(__LINE__)).c_str()
SettingWindow::SettingWindow(void* window_handler)
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window_handler, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	ImFont* font = io.Fonts->AddFontFromFileTTF("./imgui_font/simkai.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	assert(font);
}
void SettingWindow::render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin(u8"Opengl示例列表");                          // Create a window called "Hello, world!" and append into it.
	std::vector<std::string> vec_all_names;
	for (auto& s : all_reanders)
	{
		vec_all_names.push_back(s->getName());
	}
	std::vector<const char*> vec_all_names_c;
	for (auto& s : vec_all_names) {
		vec_all_names_c.push_back(s.c_str());
	}

	static int select_item = -1;
	if (!vec_all_names_c.empty() && ImGui::Combo(HIDE_LABEL, &select_item, vec_all_names_c.data(), (int)vec_all_names_c.size())) {
		auto future_render = all_reanders[select_item];
		if (using_render) {
			using_render->release();
		}

		{
			future_render->init();
			using_render = future_render;
		}
	}



	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
SettingWindow::~SettingWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}