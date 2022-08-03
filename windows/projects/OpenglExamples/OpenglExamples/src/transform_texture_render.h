#pragma once
#include "render.h"
#include "program.h"
#include "texture.h"
#include <memory>
class TransformTextureRender : public Render
{
private:
	std::shared_ptr<Program> program{};
	std::shared_ptr<Texture> m_tex{};
	GLuint m_vao{};
	GLuint m_vbo{};
	GLuint m_ebo{};
public:
	TransformTextureRender(const std::string& name_utf8) :Render(name_utf8) {};
	virtual void render()override;
	virtual void init() override;
	virtual void release()override;
};
