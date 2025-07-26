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
#include <optional>
#include <string>
#include <utility>

Window::~Window() {
  if (ptr_)
    glfwTerminate();
}

Window::Window(Window&& other) noexcept
  : ptr_(std::exchange(other.ptr_, nullptr)) {

  register_callbacks();
}

std::optional<Window> Window::create(int32 width, int32 height, const std::string& title) {

  if (!glfwInit()) {
    std::cout << "GLFW: failed to initialise" << std::endl;
    return std::nullopt;
  }

  //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!window_ptr) {
    std::cout << "GLFW: failed to create window" << std::endl;
    glfwTerminate();
    return std::nullopt;
  }

  glfwMakeContextCurrent(window_ptr);
  glfwSwapInterval(0);

#ifndef SYS_GL_HEADERS
  gladLoadGL(glfwGetProcAddress);
#endif

  int32 fb_width, fb_height;
  glfwGetFramebufferSize(window_ptr, &fb_width, &fb_height);

  glViewport(0, 0, fb_width, fb_height);

  Window window;
  window.ptr_ = window_ptr;

  return std::optional<Window>(std::move(window));
}

void Window::register_callbacks() {

  glfwSetWindowUserPointer(ptr_, this);

  auto key_la = [](GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods) -> void {
    static_cast<Window *>(glfwGetWindowUserPointer(p))->key_callback(p, key, scan, act, mods);
  };

  glfwSetKeyCallback(ptr_, key_la);
}

void Window::key_callback(GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods) {
  if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
    glfwSetWindowShouldClose(p, 1);
  if (key == GLFW_KEY_SPACE && act == GLFW_PRESS)
    std::cout << "Space pressed!!" << std::endl;
}
