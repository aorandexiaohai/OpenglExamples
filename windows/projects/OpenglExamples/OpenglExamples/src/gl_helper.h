#pragma once
#include "log.h"
#define CHECK_GL_ERROR() \
{ \
	auto error = glGetError(); \
	if(error != 0) \
	{ \
		ERROR_LOG_AND_ASSERT(std::to_string(error)+" is an opengl error"); \
	} \
}