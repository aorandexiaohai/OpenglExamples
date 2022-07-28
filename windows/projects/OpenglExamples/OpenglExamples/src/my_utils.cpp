#include "my_utils.h"
#include <fstream>
#include <sstream>
#include "log.h"
std::string ReadTextFile(const std::string& file_path)
{
	std::stringstream ss;
	std::ifstream fin(file_path);
	if (!fin) {
		ERROR_LOG_AND_ASSERT("can not read from " + std::string(file_path));
	}
	ss << fin.rdbuf();
	return ss.str();
}