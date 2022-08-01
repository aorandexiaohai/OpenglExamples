#pragma once
#include "glad/glad.h"
#include <string>
class Program
{
private:
	GLuint m_program{};
public:
	Program(const std::string& vertex_shader_file, const std::string& fragment_shader_file);
	void setInt(const std::string& value, int v);
	void use();
	~Program();
};
