#include "shader_program.hpp"

#include <cstdint>
#include <iostream>

#ifdef SYS_GL_HEADERS
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(m_ID);
}

void ShaderProgram::CompileShader(uint32_t type, const std::string &src) {

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

  m_ShaderIDs.push_back(shader_id);
}

void ShaderProgram::CreateProgram() {

  m_ID = glCreateProgram();

  for (const auto &shader_id : m_ShaderIDs) {
    glAttachShader(m_ID, shader_id);
  }

  glLinkProgram(m_ID);

  int32_t result;
  glGetProgramiv(m_ID, GL_LINK_STATUS, &result);

  if (result == GL_FALSE) {

    std::cout << "Failed to create shader program\n"
              << "Linking error:\n\n"
              << std::flush;

    char msg[512];
    glGetProgramInfoLog(m_ID, 512, nullptr, msg);

    std::cout << msg << std::endl;
  }

  for (const auto &shader_id : m_ShaderIDs) {
    glDeleteShader(shader_id);
  }
}

void ShaderProgram::SetBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int32_t) value);
}

void ShaderProgram::SetFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::SetInt(const std::string &name, int32_t value) const {
  glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}

void ShaderProgram::SetMat4(const std::string &name, float *values) const {
  glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, values);
}

void ShaderProgram::Use() const {
  glUseProgram(m_ID);
}
