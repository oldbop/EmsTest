#include "window.hpp"

#include "integers.hpp"

#ifdef SYS_GL_HEADERS
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

#include <GLFW/glfw3.h>

#include <stdexcept>
#include <string>

Window::Window(int32 width, int32 height, const std::string& title)
  : ptr_(nullptr, nullptr) {

  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *win = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!win) {
    glfwTerminate();
    throw std::runtime_error("GLFW: failed to create window");
  }

  ptr_ = { win, glfwDestroyWindow };

  glfwMakeContextCurrent(ptr_.get());
  glfwSwapInterval(1);

#ifndef SYS_GL_HEADERS
  gladLoadGL(glfwGetProcAddress);
#endif

  Size<int32> size = get_size();

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glViewport(0, 0, size.width, size.height);

  glfwSetWindowUserPointer(ptr_.get(), this);

  auto resize_cb = [](GLFWwindow *win, int32 width, int32 height) -> void {
    static_cast<Window *>(glfwGetWindowUserPointer(win))->resize_cb(win, width, height);
  };

  auto key_cb = [](GLFWwindow *win, int32 key, int32 scan, int32 act, int32 mods) -> void {
    static_cast<Window *>(glfwGetWindowUserPointer(win))->key_cb(win, key, scan, act, mods);
  };

  glfwSetFramebufferSizeCallback(ptr_.get(), resize_cb);
  glfwSetKeyCallback(ptr_.get(), key_cb);



}

Size<int32> Window::get_size() const {

  Size<int32> size;
  glfwGetFramebufferSize(ptr_.get(), &size.width, &size.height);
  
  return size;
}

std::string Window::get_title() const {

  std::string title = glfwGetWindowTitle(ptr_.get());
  
  return title;
}
