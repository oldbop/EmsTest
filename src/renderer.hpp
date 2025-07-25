#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "camera.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

class Window;

class Renderer {
  friend class Window;
public:
  Renderer();
  void render(float time);
private:
  Camera cam_;
  Mesh mesh_;
  ShaderProgram prog_;
};

#endif
