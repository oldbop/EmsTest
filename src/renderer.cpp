#include "renderer.hpp"

#include "util/file_handling.hpp"

#ifdef SYS_GL_HEADERS
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

#include <string>

Renderer::Renderer()
  : cam_({})
  , mesh_({})
  , prog_({}) {

  std::string vert = load_file("res/shaders/square.vert");
  std::string frag = load_file("res/shaders/square.frag");

  prog_.compile_shader(GL_VERTEX_SHADER, vert);
  prog_.compile_shader(GL_FRAGMENT_SHADER, frag);
  prog_.create_program();
}

void Renderer::render(float time) {

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  mesh_.bind();
  prog_.use();

  mat4 model  = mat4_rotY(time * PI * 0.25f);
  mat4 camera = cam_.get_transform();

  prog_.set_mat4("M", model.v);
  prog_.set_mat4("PV", camera.v);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *) 0);
}
