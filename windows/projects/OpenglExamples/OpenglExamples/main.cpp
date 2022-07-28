#include <iostream>
#include "setting_window.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "render.h"
#include "render_hello_triangle.h"
#include "render_hello_quadangle.h"
#include "render_hello_quadangle_index.h"

std::vector<std::shared_ptr<Render>> all_reanders{};
std::shared_ptr<Render> using_render{};
SettingWindow* using_setting_window{};
GLFWwindow* global_window{};
GLFWwindow* InitWindows();
void redraw();


void framebuff_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	redraw();
}

void process_input_callabck(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {

	auto window = InitWindows();

	{
		all_reanders.push_back(std::make_shared<RenderHelloTriangle>(u8"三角形"));
		all_reanders.push_back(std::make_shared<RenderHelloQuadangle>(u8"四边形(非索引)"));
		all_reanders.push_back(std::make_shared<RenderHelloQuadangleIndex>(u8"四边形(索引)"));
	}

	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	{
		SettingWindow sw(window);
		using_setting_window = &sw;
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			//render.
			{
				redraw();
			}
		}

		using_setting_window = nullptr;
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

GLFWwindow* InitWindows()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//绘画区域透明
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLTest", NULL, NULL);
	global_window = window;

	//无边框
	//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window " << std::endl;
		glfwTerminate();
		std::exit(-1);
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, process_input_callabck);
	glfwSetFramebufferSizeCallback(window, framebuff_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::exit(-1);
	}

	return window;
}

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	if (using_setting_window)
	{
		using_setting_window->render();
	}
	if (using_render) {
		using_render->render();
	}
	glfwSwapBuffers(global_window);
}