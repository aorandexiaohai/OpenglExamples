#pragma once
#include "glad/glad.h"
#include <string>
class Shader
{
  public:
    static GLuint loadShader(GLenum shader_type, const std::string &shader_source_code);
};