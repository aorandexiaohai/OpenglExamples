#pragma once
#include "render.h"
#include "program.h"
#include <memory>
class RenderColorTriangle : public Render
{
private:
	std::shared_ptr<Program> program{};
	GLuint m_vao{};
	GLuint m_vbo{};
public:
	RenderColorTriangle(const std::string& name_utf8) :Render(name_utf8) {};
	virtual void render()override;
	virtual void init() override;
	virtual void release()override;
};
