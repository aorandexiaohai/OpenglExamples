#include "render_hello_triangle.h"
#include "gl_helper.h"


void RenderHelloTriangle::render()
{
	// Use the program object
	program->use();
	// Load the vertex data
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void RenderHelloTriangle::init()
{
	program = std::make_shared<Program>("render_1.vs", "render_1.fs");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f };

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void RenderHelloTriangle::release()
{
	program = {};
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}