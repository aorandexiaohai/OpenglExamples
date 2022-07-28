#include "setting_window.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <vector>
#include <memory>
#include <sstream>
#include "render.h"
#include "glad/glad.h"

extern std::vector<std::shared_ptr<Render>> all_reanders;
extern std::shared_ptr<Render> using_render;
#define HIDE_LABEL ("##" + std::to_string(__LINE__)).c_str()

static uint64_t dynamic_label{};
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

	ImFont* font = io.Fonts->AddFontFromFileTTF("./imgui_font/simkai.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	assert(font);
}

template<class T>
std::string toStr(const T& t) {
	std::stringstream ss;
	ss << t;
	return ss.str();
}

bool show_slider_float(const std::string& slider_info_utf8, float min_value, float max_value, float* value, const char* unique_label)
{
	auto label = slider_info_utf8 + ":" + toStr(min_value);
	ImGui::Text(label.c_str());
	ImGui::SameLine();
	auto x = ImGui::SliderFloat(unique_label, value, min_value, max_value);
	ImGui::SameLine();
	ImGui::Text(toStr(max_value).c_str());
	return x;
}

void SettingWindow::render()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin(u8"设置");                          // Create a window called "Hello, world!" and append into it.

	if (ImGui::CollapsingHeader(u8"渲染设置")) {
		//static int is_fill = true;
		static size_t mode = GL_FILL;
		if (ImGui::RadioButton(u8"填充模式", mode == GL_FILL)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mode = GL_FILL;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton(u8"线框模式", mode == GL_LINE)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			mode = GL_LINE;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton(u8"点模式", mode == GL_POINT)) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			mode = GL_POINT;
		}
		if (mode == GL_LINE) {
			static float line_width = 1;
			if (show_slider_float(u8"线宽", 1, 10, &line_width, HIDE_LABEL)) {
				glLineWidth(line_width);
			}
		}
		if (mode == GL_POINT) {
			static float point_size = 1;
			if (show_slider_float(u8"点大小", 1, 10, &point_size, HIDE_LABEL)) {
				glPointSize(point_size);
			}
		}
	}

	if (ImGui::CollapsingHeader(u8"Opengl示例列表"))
	{
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