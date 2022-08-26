#include "camera_cube_render.h"
#include "camera_cube_render_2.h"
#include "cube_render.h"
#include "glad/glad.h"
#include "more_cubes_render.h"
#include "render.h"
#include "render_color_triangle.h"
#include "render_hello_quadangle.h"
#include "render_hello_quadangle_index.h"
#include "render_hello_triangle.h"
#include "setting_window.h"
#include "texture_render.h"
#include "transform_texture_render.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <numeric>
#include <thread>
#include <vector>

std::vector<std::shared_ptr<Render>> all_reanders{};
std::shared_ptr<Render> using_render{};
SettingWindow *using_setting_window{};
GLFWwindow *global_window{};
GLFWwindow *InitWindows();
double last_fps = 0.0f;

void redraw();

void framebuff_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    redraw();
}

void process_input_callabck(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if (using_render)
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            using_render->m_context.press_list['w'] = true;
            using_render->m_context.press_list['W'] = true;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            using_render->m_context.press_list['s'] = true;
            using_render->m_context.press_list['S'] = true;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            using_render->m_context.press_list['a'] = true;
            using_render->m_context.press_list['A'] = true;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            using_render->m_context.press_list['d'] = true;
            using_render->m_context.press_list['D'] = true;
        }
    }
}

int main()
{

    auto window = InitWindows();

    {
        all_reanders.push_back(std::make_shared<RenderHelloTriangle>(u8"三角形"));
        all_reanders.push_back(std::make_shared<RenderHelloQuadangle>(u8"四边形(非索引)"));
        all_reanders.push_back(std::make_shared<RenderHelloQuadangleIndex>(u8"四边形(索引)"));
        all_reanders.push_back(std::make_shared<RenderColorTriangle>(u8"带颜色的三角形"));
        all_reanders.push_back(std::make_shared<TextureRender>(u8"纹理"));
        all_reanders.push_back(std::make_shared<TransformTextureRender>(u8"几何操作纹理"));
        all_reanders.push_back(std::make_shared<CubeRender>(u8"带纹理的立方体"));
        all_reanders.push_back(std::make_shared<MoreCubesRender>(u8"更多的带纹理立方体"));
        all_reanders.push_back(std::make_shared<CameraCubeRender>(u8"让摄像机动起来"));
        all_reanders.push_back(std::make_shared<CameraCubeRender2>(u8"会移动的摄像机"));
    }

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    {
        SettingWindow sw(window);
        using_setting_window = &sw;
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();

            // render.
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

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (using_render)
    {
        using_render->m_context.m_last_x = using_render->m_context.m_current_x;
        using_render->m_context.m_last_y = using_render->m_context.m_current_y;
        using_render->m_context.m_current_x = xpos;
        using_render->m_context.m_current_y = ypos;
    }
}

GLFWwindow *InitWindows()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //绘画区域透明
    // glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGLTest", NULL, NULL);
    global_window = window;

    //无边框
    // glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window " << std::endl;
        glfwTerminate();
        std::exit(-1);
    }
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, process_input_callabck);
    glfwSetFramebufferSizeCallback(window, framebuff_size_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        std::exit(-1);
    }

    return window;
}

void redraw()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (using_setting_window)
    {
        using_setting_window->render();
    }
    last_fps = 0.0;
    if (using_render)
    {
        static std::list<float> all;
        auto begin = glfwGetTime();
        const float maximal_fps = 120.0f;
        {
            auto t1 = glfwGetTime();
            using_render->render();
            using_render->m_context.reset();
            auto t2 = glfwGetTime();
            auto left_time = 1000.0f / maximal_fps - (t2 - t1) * 1000.0f;
            if (left_time > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds((int)(left_time + 0.5)));
            }
        }
        //统计近30帧的平均帧率
        all.push_back(glfwGetTime() - begin);
        if (all.size() >= 30)
        {
            all.pop_front();
        }
        last_fps = std::accumulate(all.begin(), all.end(), 0.0f);
        last_fps /= all.size();
        last_fps = 1.0f / last_fps;
    }
    glfwSwapBuffers(global_window);
}