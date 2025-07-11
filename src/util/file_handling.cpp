#include "file_handling.hpp"

#include <cstdio>
#include <string>

std::string load_file(const char *path) {

  std::FILE *file = std::fopen(path, "rb");

  if (!file) {
    return std::string();
  }

  std::string data;
  std::fseek(file, 0, SEEK_END);
  data.resize(std::ftell(file));

  std::fseek(file, 0, SEEK_SET);
  std::fread(&(data[0]), 1, data.size(), file);
  std::fclose(file);

  return data;
}
