#include "render_hello_triangle.h"
#include "gl_helper.h"


void RenderHelloTriangle::render()
{
	// Use the program object
	program->use();
	// Load the vertex data
	
	CHECK_GL_ERROR();
	glBindVertexArray(m_vao);
	CHECK_GL_ERROR();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	CHECK_GL_ERROR();
	glFlush();
}
void RenderHelloTriangle::init()
{
	program = std::make_shared<Program>("render_hello_triangle.vs", "render_hello_triangle.fs");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f };

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
	program->use();
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