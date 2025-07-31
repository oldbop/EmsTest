#include "file_handling.hpp"

#include <cstdio>
#include <iostream>
#include <string>

std::string load_file(const std::string& path) {

  std::FILE *file = std::fopen(path.c_str(), "rb");

  if (!file) {
    std::cout << "Failed to load file: " << path << std::endl;
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
