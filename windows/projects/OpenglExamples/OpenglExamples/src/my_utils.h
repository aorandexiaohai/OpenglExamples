#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
std::string ReadTextFile(const std::string &file_path);
// rgba
std::vector<uint8_t> ReadPictureFiles(const std::string &file_path, int &width, int &height);
static float randfloat(float min_v, float max_v)
{
    auto diff = max_v - min_v;
    return float(rand()) / float((RAND_MAX)) * diff + min_v;
}