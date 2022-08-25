#include "shader.h"
#include "log.h"
#include <stdlib.h>
GLuint Shader::loadShader(GLenum shader_type, const std::string &shader_source_code)
{
    GLuint shader;
    GLint compiled;
    // Create the shader object
    shader = glCreateShader(shader_type);
    if (shader == 0)
    {
        ERROR_LOG_AND_ASSERT("glCreateShader");
        return 0;
    }
    const char *shaderSrc = shader_source_code.c_str();
    // Load the shader source
    glShaderSource(shader, 1, &shaderSrc, NULL);
    // Compile the shader
    glCompileShader(shader);
    // Check the compile status
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        GLint infoLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        if (infoLen > 1)
        {
            char *infoLog = (char *)malloc(sizeof(char) * (infoLen + 1));
            infoLog[infoLen] = 0;
            glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
            ERROR_LOG_AND_ASSERT(infoLog);
            free(infoLog);
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}