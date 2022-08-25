#include "texture.h"
#include "my_utils.h"
Texture::Texture(const char *file_name)
{
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);
    {
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                        GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    int width{};
    int height{};
    auto data = ReadPictureFiles(file_name, width, height);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
    //不清楚为啥必须调用这句代码
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
Texture::~Texture()
{
    glDeleteTextures(1, &m_tex);
}