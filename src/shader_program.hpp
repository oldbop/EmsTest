#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <cstdint>
#include <string>
#include <vector>

class ShaderProgram {
public:
  void compile_shader(uint32_t type, const std::string& src);
  void create_program();
  uint32_t get_id() const { return id_; }
  void set_bool(const std::string& name, bool value) const;
  void set_float(const std::string& name, float value) const;
  void set_int(const std::string& name, int32_t value) const;
  void set_mat4(const std::string& name, const float *values) const;
  void use() const;
private:
  uint32_t id_ = 0;
  std::vector<uint32_t> shader_ids_;
};

#endif
