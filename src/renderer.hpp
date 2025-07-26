#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "camera.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

class Window;

class Renderer {
  friend class Window;
public:
  Renderer(Mesh mesh, ShaderProgram prog, Camera cam);
  void render(float time);
private:
  Mesh mesh_;
  ShaderProgram prog_;
  Camera cam_;
};

#endif
