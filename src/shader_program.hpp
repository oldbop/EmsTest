#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "integers.hpp"

#include <string>
#include <utility>
#include <vector>

class ShaderProgram {
public:
  ShaderProgram() = default;
  ~ShaderProgram();
  ShaderProgram(const ShaderProgram&) = delete;
  ShaderProgram& operator=(const ShaderProgram&) = delete;
  ShaderProgram(ShaderProgram&& other) noexcept;
  ShaderProgram& operator=(ShaderProgram&& other) noexcept;

  void compile_shader(uint32 type, const std::string& src);
  void create_program();
  void use() const;
  uint32 get_id() const { return id_; }
  void set_bool(const std::string& name, bool value);
  void set_float(const std::string& name, float value);
  void set_int(const std::string& name, int32 value);
  void set_mat4(const std::string& name, const float *values);
private:
  uint32 id_ = 0;
  std::vector<uint32> shader_ids_;

  void swap(ShaderProgram& other) noexcept {
    std::swap(id_, other.id_);
    std::swap(shader_ids_, other.shader_ids_);
  }
};

#endif
