#include "render_hello_quadangle.h"
#include "gl_helper.h"


void RenderHelloQuadangle::render()
{
	// Use the program object
	program->use();
	// Load the vertex data
	glBindVertexArray(m_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
void RenderHelloQuadangle::init()
{
	program = std::make_shared<Program>("render_hello_triangle.vs", "render_hello_triangle.fs");

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	GLfloat vVertices[] = { 
		// 第一个三角形
		  0.5f, 0.5f, 0.0f,   // 右上角
		  0.5f, -0.5f, 0.0f,  // 右下角
		  -0.5f, 0.5f, 0.0f,  // 左上角
		  // 第二个三角形
		  0.5f, -0.5f, 0.0f,  // 右下角
		  -0.5f, -0.5f, 0.0f, // 左下角
		  -0.5f, 0.5f, 0.0f   // 左上角
	};

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vVertices), vVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void RenderHelloQuadangle::release()
{
	program = {};
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}