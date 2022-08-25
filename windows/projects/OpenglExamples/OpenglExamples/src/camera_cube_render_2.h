#pragma once
#include "render.h"
#include "program.h"
#include "texture.h"
#include "camera.h"
#include <memory>
class CameraCubeRender2 : public Render
{
private:
	std::shared_ptr<Program> program{};
	GLuint m_vao{};
	GLuint m_vbo{};
	std::shared_ptr<Texture> m_tex{};
	std::shared_ptr<Camera> m_camera{};
	float m_last_time{};
public:
	CameraCubeRender2(const std::string& name_utf8) :Render(name_utf8) {};
	virtual void render()override;
	virtual void init() override;
	virtual void release()override;
};
