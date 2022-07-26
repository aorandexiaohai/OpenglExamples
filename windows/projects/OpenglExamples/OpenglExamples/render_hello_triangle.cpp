#include "render_hello_triangle.h"


void RenderHelloTriangle::render()
{
	GLfloat vVertices[] = { 0.0f, 0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f };
	// Use the program object
	program->use();
	// Load the vertex data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
void RenderHelloTriangle::init()
{
	program = std::make_shared<Program>("render_hello_triangle.vs", "render_hello_triangle.fs");
}
void RenderHelloTriangle::release()
{
	program = {};
}