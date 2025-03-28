#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include <cstdint>
#include <string>
#include <vector>

class ShaderProgram {
public:
  void CompileShader(uint32_t type, const std::string &src);
  void CreateProgram();
  uint32_t GetID() const { return m_ID; }
  void SetBool(const std::string &name, bool value) const;
  void SetFloat(const std::string &name, float value) const;
  void SetInt(const std::string &name, int32_t value) const;
  void SetMat4(const std::string &name, float *values) const;
  void Use() const;
private:
  uint32_t m_ID;
  std::vector<uint32_t> m_ShaderIDs;
};

#endif
