#include "more_cubes_render.h"
#include "gl_helper.h"
#include "my_utils.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

void MoreCubesRender::render()
{
    // Use the program object
    program->use();
    program->setInt("ourTexture", 0); // or with shader class
    {
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::ortho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);
        program->setFloat16("projection",
                            glm::value_ptr(projection)); // note: currently we set the projection matrix each frame, but
                                                         // since the projection matrix rarely changes it's often best
                                                         // practice to set it outside the main loop only once.
        program->setFloat16("view", glm::value_ptr(view));
    }

    glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, m_tex->getTexId());
    // Load the vertex data
    glBindVertexArray(m_vao);
    static std::vector<glm::vec3> positions{};
#define MAX_CUBES 200
    if (positions.empty())
    {
        for (int i = 0; i < MAX_CUBES; i++)
        {
            positions.emplace_back(randfloat(-10, 10), randfloat(-10, 10), randfloat(-10, 10));
        }
    }
    for (int i = 0; i < MAX_CUBES; i++)
    {
        glm::mat4 model(1.0f);
        float angle = 20.0f * (i + glfwGetTime());
        model = glm::translate(model, positions[i]);
        model = glm::rotate(model, glm::radians((float)(angle)), glm::vec3(1.0f, 0.3f, 0.5f));
        program->setFloat16("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
void MoreCubesRender::init()
{
    program = std::make_shared<Program>("render_5.vs", "render_5.fs");
    m_tex = std::make_shared<Texture>("girl.jpg");

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
void MoreCubesRender::release()
{
    program = {};
    m_tex = {};
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}