#ifndef MESH_HPP
#define MESH_HPP

#include "integers.hpp"

#ifdef SYS_GL_HEADERS
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

static float vertices[] = {
  -0.5f, -0.5f,  0.5f,
  -0.5f,  0.5f,  0.5f,
   0.5f, -0.5f,  0.5f,
   0.5f,  0.5f,  0.5f,

  -0.5f, -0.5f, -0.5f,
  -0.5f,  0.5f, -0.5f,
   0.5f, -0.5f, -0.5f,
   0.5f,  0.5f, -0.5f
};

static uint32 indices[] = {
  0, 2, 3, 3, 1, 0,
  4, 0, 1, 1, 5, 4,
  6, 4, 5, 5, 7, 6,
  2, 6, 7, 7, 3, 2,
  1, 3, 7, 7, 5, 1,
  4, 6, 2, 2, 0, 4
};

class Mesh {
public:
  Mesh();
  ~Mesh();
  Mesh(const Mesh&) = delete;
  Mesh& operator=(const Mesh&) = delete;
  Mesh(Mesh&& other) noexcept;
  Mesh& operator=(Mesh&& other) noexcept;

  void bind() const { glBindVertexArray(vao_); }
  void unbind() const { glBindVertexArray(0); }
private:
  uint32 vao_;
  uint32 vbo_;
  uint32 ebo_;
};

#endif
