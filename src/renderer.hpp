#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "camera.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"
#include "window.hpp"

class Renderer {
public:
  Renderer(const Window& win, Mesh mesh, ShaderProgram prog, Camera cam);
  void render(float time);
private:
  Mesh mesh_;
  ShaderProgram prog_;
  Camera cam_;
};

#endif
