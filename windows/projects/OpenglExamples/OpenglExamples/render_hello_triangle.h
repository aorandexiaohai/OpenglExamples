#pragma once
#include "render.h"
#include "program.h"
#include <memory>
class RenderHelloTriangle : public Render
{
private:
	std::shared_ptr<Program> program{};
public:
	RenderHelloTriangle() :Render("RenderHelloTriangle") {};
	virtual void render()override;
	virtual void init() override;
	virtual void release()override;
};
