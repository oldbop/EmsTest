#include "file_handling.hpp"

#include <cstdio>
#include <string>

std::string load_file(const char *path) {

  FILE *file = fopen(path, "rb");

  if (!file) {
    return nullptr;
  }

  std::string data;

  fseek(file, 0, SEEK_END);
  data.resize(ftell(file));
  fseek(file, 0, SEEK_SET);

  fread(&(data[0]), 1, data.size(), file);

  fclose(file);

  return data;
}
