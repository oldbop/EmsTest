#include "renderer.hpp"

#include "camera.hpp"
#include "integers.hpp"
#include "mesh.hpp"
#include "shader_program.hpp"

#ifdef SYS_GL_HEADERS
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

#include <string>
#include <utility>

Renderer::Renderer(Mesh mesh, ShaderProgram prog, Camera cam)
  : mesh_(std::move(mesh))
  , prog_(std::move(prog))
  , cam_(cam) {

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Renderer::render(float time, int32 width, int32 height) {

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  mesh_.bind();
  prog_.use();

  mat4 model  = mat4_rotY(time * PI * 0.25f);
  mat4 camera = cam_.get_transform(width, height);

  prog_.set_mat4("M", model.v);
  prog_.set_mat4("PV", camera.v);

  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *) 0);
}
