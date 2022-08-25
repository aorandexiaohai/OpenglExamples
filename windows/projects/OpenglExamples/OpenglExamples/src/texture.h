#pragma once
#include <glad/glad.h>
class Texture
{
  private:
    GLuint m_tex{};

  public:
    Texture(const char *file_name);
    ~Texture();
    GLuint getTexId() const
    {
        return m_tex;
    }
};