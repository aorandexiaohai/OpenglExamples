#pragma once
#include "render.h"
#include "program.h"
#include <memory>
class RenderHelloTriangle : public Render
{
private:
	std::shared_ptr<Program> program{};
public:
	RenderHelloTriangle(const std::string& name_utf8 = "RenderHelloTriangle") :Render(name_utf8) {};
	virtual void render()override;
	virtual void init() override;
	virtual void release()override;
};
