#include <iostream>
#include "setting_window.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

GLFWwindow* InitWindows();


void framebuff_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void process_input_callabck(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {

	auto window = InitWindows();

	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glfwSetFramebufferSizeCallback(window, framebuff_size_callback);
	{
		SettingWindow sw(window);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			//render.
			{
				glClear(GL_COLOR_BUFFER_BIT);
				sw.render();
				glfwSwapBuffers(window);
			}
		}
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

	//无边框
	//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window " << std::endl;
		glfwTerminate();
		std::exit(-1);
	}
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, process_input_callabck);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::exit(-1);
	}
	return window;
}