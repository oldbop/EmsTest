#include "shader_program.hpp"
#include "util/file_handling.hpp"

#include <cstdint>
#include <iostream>
#include <string>

#include <slim/slim.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#ifdef SYS_GL_HEADERS
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

#ifdef EMSCRIPTEN
#include <emscripten.h>

#endif

struct Renderer {
  std::string title;
  uint32_t width, height;
  GLFWwindow *win;
};

static Renderer rdr = { "Rotating square", 700, 700 };

void render(void *shader_program) {

  float time = glfwGetTime();

  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  mat4 rotX, rotY, rotZ;

  //mat4_rotX(rotX, time * PI * 0.2f);
  mat4_rotY(rotY, time * PI * 1.2f);
  mat4_rotZ(rotZ, time * PI / 4.0f);

  mat4_mul(rotY, rotZ);
  //mat4_mul(rotX, rotY);

  mat4_tsp(rotY);
  
  ((ShaderProgram *) shader_program)->SetMat4("Rot", rotY);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) 0);

  glfwSwapBuffers(rdr.win);
  glfwPollEvents();
}

int main(int argc, char **argv) {

  if (!glfwInit()) {
    std::cout << "GLFW: failed to initialise" << std::endl;
    return 1;
  }

  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  rdr.win = glfwCreateWindow(rdr.width, rdr.height, rdr.title.c_str(), nullptr, nullptr);

  if (!rdr.win) {
    std::cout << "GLFW: failed to create window" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(rdr.win);
  glfwSwapInterval(1);

#ifndef SYS_GL_HEADERS
  gladLoadGL(glfwGetProcAddress);
#endif

  auto resize_cb = [](GLFWwindow *win, int32_t width, int32_t height) -> void {
    
    glViewport(0, 0, width, height);
    
    rdr.width  = width;
    rdr.height = height;
  };

  auto key_cb = [](GLFWwindow *win, int32_t key, int32_t scan, int32_t act, int32_t mods) -> void {
    if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
      glfwSetWindowShouldClose(win, 1);
  };

  glfwSetFramebufferSizeCallback(rdr.win, resize_cb);
  glfwSetKeyCallback(rdr.win, key_cb);

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);
  //glLineWidth(8.0f);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glViewport(0, 0, rdr.width, rdr.height);

  float vertices[] = {
    /*   Positions   */   /*   Colours   */
    -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
     0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f
  };

  uint32_t indices[] = { 0, 2, 3, 3, 1, 0 };

  uint32_t vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  uint32_t vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  uint32_t ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  std::string vert = load_file("res/shaders/square.vert");
  std::string frag = load_file("res/shaders/square.frag");

  ShaderProgram prog;

  prog.CompileShader(GL_VERTEX_SHADER, vert);
  prog.CompileShader(GL_FRAGMENT_SHADER, frag);
  prog.CreateProgram();
  prog.Use();

#ifdef EMSCRIPTEN
  emscripten_set_main_loop_arg(render, &prog, 60, true);
#else
  while (!glfwWindowShouldClose(rdr.win)) {
    render(&prog);
  }
#endif

  glfwTerminate();
  return 0;
}
