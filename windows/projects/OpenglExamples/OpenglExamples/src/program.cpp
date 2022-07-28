#include "program.h"
#include "shader.h"
#include "my_utils.h"
#include "log.h"
#include <stdlib.h>
Program::Program(const std::string& vertex_shader_file, const std::string& fragment_shader_file)
{
	auto vertexShader = Shader::loadShader(GL_VERTEX_SHADER, ReadTextFile(vertex_shader_file));
	auto fragmentShader = Shader::loadShader(GL_FRAGMENT_SHADER, ReadTextFile(fragment_shader_file));
	m_program = glCreateProgram();
	ERROR_LOG_AND_ASSERT_IF_TRUE(m_program == 0);
	glAttachShader(m_program, vertexShader);
	glAttachShader(m_program, fragmentShader);
	// Link the program
	glLinkProgram(m_program);
	// Check the link status
	GLint linked{};
	glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLint infoLen = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLen);
		if (infoLen > 1)
		{
			char* infoLog = (char*)malloc(sizeof(char) * (infoLen+1));
			infoLog[infoLen] = 0;
			glGetProgramInfoLog(m_program, infoLen, NULL, infoLog);
			ERROR_LOG_AND_ASSERT(infoLog);
			free(infoLog);
		}
		glDeleteProgram(m_program);
	}
}
void Program::use()
{
	glUseProgram(m_program);
}
Program::~Program()
{
	glDeleteProgram(m_program);
}