#include "shader_program.hpp"

#include <cstdint>
#include <iostream>

#ifdef SYS_GL_HEADERS
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

void ShaderProgram::compile_shader(uint32_t type, const std::string& src) {

  const char *c_style = src.c_str();
  uint32_t shader_id  = glCreateShader(type);

  glShaderSource(shader_id, 1, &c_style, nullptr);
  glCompileShader(shader_id);

  int32_t result;
  glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

  if (result == GL_FALSE) {

    std::cout << "Shader compilation failed\n"
              << "Compilation error:\n\n"
              << std::flush;

    char msg[512];
    glGetShaderInfoLog(shader_id, 512, nullptr, msg);

    std::cout << msg << std::endl;

    glDeleteShader(shader_id);
    return;
  }

  shader_ids_.push_back(shader_id);
}

void ShaderProgram::create_program() {

  id_ = glCreateProgram();

  for (const auto& shader_id : shader_ids_) {
    glAttachShader(id_, shader_id);
  }

  glLinkProgram(id_);

  int32_t result;
  glGetProgramiv(id_, GL_LINK_STATUS, &result);

  if (result == GL_FALSE) {

    std::cout << "Failed to create shader program\n"
              << "Linking error:\n\n"
              << std::flush;

    char msg[512];
    glGetProgramInfoLog(id_, 512, nullptr, msg);

    std::cout << msg << std::endl;
  }

  for (const auto& shader_id : shader_ids_) {
    glDetachShader(id_, shader_id);
    glDeleteShader(shader_id);
  }

  shader_ids_.clear();
}

void ShaderProgram::set_bool(const std::string& name, bool value) const {
  glUniform1i(glGetUniformLocation(id_, name.c_str()), (int32_t) value);
}

void ShaderProgram::set_float(const std::string& name, float value) const {
  glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
}

void ShaderProgram::set_int(const std::string& name, int32_t value) const {
  glUniform1i(glGetUniformLocation(id_, name.c_str()), value);
}

void ShaderProgram::set_mat4(const std::string& name, const float *values) const {
  glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, GL_FALSE, values);
}

void ShaderProgram::use() const {
  glUseProgram(id_);
}

ShaderProgram::~ShaderProgram() {

  for (const auto& shader_id : shader_ids_) {
    glDeleteShader(shader_id);
  }

  glUseProgram(0);
  glDeleteProgram(id_);
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept : ShaderProgram() {
  swap(other);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) noexcept {

  ShaderProgram prog(std::move(other));
  swap(prog);

  return *this;
}
