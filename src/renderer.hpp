#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "camera.hpp"
#include "integers.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

class Renderer {
public:
  Renderer(Mesh mesh, ShaderProgram prog, Camera cam);
  void render(float time, int32 width, int32 height);
private:
  Mesh mesh_;
  ShaderProgram prog_;
  Camera cam_;
};

#endif
