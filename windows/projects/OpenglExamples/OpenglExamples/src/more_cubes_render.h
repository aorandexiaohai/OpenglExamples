#pragma once
#include "program.h"
#include "render.h"
#include "texture.h"
#include <memory>
class MoreCubesRender : public Render
{
  private:
    std::shared_ptr<Program> program{};
    GLuint m_vao{};
    GLuint m_vbo{};
    std::shared_ptr<Texture> m_tex{};

  public:
    MoreCubesRender(const std::string &name_utf8) : Render(name_utf8){};
    virtual void render() override;
    virtual void init() override;
    virtual void release() override;
};
