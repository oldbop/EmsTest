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
  uint32 get_id() const { return id_; }
  void set_bool(const std::string& name, bool value) const;
  void set_float(const std::string& name, float value) const;
  void set_int(const std::string& name, int32 value) const;
  void set_mat4(const std::string& name, const float *values) const;
  void use() const;
private:
  uint32 id_ = 0;
  std::vector<uint32> shader_ids_;

  void swap(ShaderProgram& other) noexcept {
    std::swap(id_, other.id_);
    std::swap(shader_ids_, other.shader_ids_);
  }
};

#endif
