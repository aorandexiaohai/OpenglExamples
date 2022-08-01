#pragma once
#include <string>
#include <vector>
#include <stdint.h>
std::string ReadTextFile(const std::string& file_path);
//rgba
std::vector<uint8_t> ReadPictureFiles(const std::string& file_path, int& width, int& height);