#include "window.hpp"

#include "integers.hpp"

#ifdef SYS_GL_HEADERS
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

bool Window::init(int32 width, int32 height, const std::string& title) {

  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!win) {
    glfwTerminate();
    return false;
  }

  ptr_ = { win, glfwDestroyWindow };

  glfwMakeContextCurrent(ptr_.get());
  glfwSwapInterval(1);

#ifndef SYS_GL_HEADERS
  gladLoadGL(glfwGetProcAddress);
#endif

  int32 fb_width, fb_height;

  glfwGetFramebufferSize(ptr_.get(), &fb_width, &fb_height);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glViewport(0, 0, fb_width, fb_height);

  cam_.set_aspect(static_cast<float>(fb_width) / static_cast<float>(fb_height));

  glfwSetWindowUserPointer(ptr_.get(), this);

  auto resize_cb = [](GLFWwindow *win, int32 width, int32 height) -> void {
    static_cast<Window *>(glfwGetWindowUserPointer(win))->resize_cb(win, width, height);
  };

  auto key_cb = [](GLFWwindow *win, int32 key, int32 scan, int32 act, int32 mods) -> void {
    static_cast<Window *>(glfwGetWindowUserPointer(win))->key_cb(win, key, scan, act, mods);
  };

  glfwSetFramebufferSizeCallback(ptr_.get(), resize_cb);
  glfwSetKeyCallback(ptr_.get(), key_cb);

  return true;
}

void Window::resize_cb(GLFWwindow *win, int32 width, int32 height) {
  glViewport(0, 0, width, height);
  cam_.set_aspect(static_cast<float>(width) / static_cast<float>(height));
}

void Window::key_cb(GLFWwindow *win, int32 key, int32 scan, int32 act, int32 mods) {

  if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS) {
    glfwSetWindowShouldClose(win, 1);
  }
  if (key == GLFW_KEY_SPACE && act == GLFW_PRESS) {
    std::cout << "Space pressed!!" << std::endl;
  }
}
