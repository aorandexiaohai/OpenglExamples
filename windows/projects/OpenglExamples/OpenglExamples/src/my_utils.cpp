#include "my_utils.h"
#include <fstream>
#include <sstream>
#include "log.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

std::vector<uint8_t> ReadPictureFiles(const std::string& file_path, int& width, int& height)
{
	stbi_set_flip_vertically_on_load(true);

	int nrChannels;
	unsigned char* data = stbi_load(file_path.c_str(), &width, &height, &nrChannels, 4);
	ERROR_LOG_AND_ASSERT_IF_FALSE(data);

	auto total = width * height * 4;
	std::vector<uint8_t> r(total, 0);
	memcpy(r.data(), data, total);
	STBI_FREE(data);
	return r;
}