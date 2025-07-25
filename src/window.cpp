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
  : ptr_(std::exchange(other.ptr_, nullptr))
  , rdr_(std::move(other.rdr_)) {

  int32 fb_width, fb_height;

  glfwGetFramebufferSize(ptr_, &fb_width, &fb_height);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glViewport(0, 0, fb_width, fb_height);

  rdr_.cam_.htow = static_cast<float>(fb_height) / static_cast<float>(fb_width);

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

  Window window;
  window.ptr_ = window_ptr;

  return std::optional<Window>(std::move(window));
}

void Window::run() {

  rdr_.render(glfwGetTime());

  glfwSwapBuffers(ptr_);
  glfwPollEvents();
}

void Window::register_callbacks() {

  glfwSetWindowUserPointer(ptr_, this);

  auto resize_la = [](GLFWwindow *p, int32 width, int32 height) -> void {
    static_cast<Window *>(glfwGetWindowUserPointer(p))->resize_callback(p, width, height);
  };

  auto key_la = [](GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods) -> void {
    static_cast<Window *>(glfwGetWindowUserPointer(p))->key_callback(p, key, scan, act, mods);
  };

  glfwSetFramebufferSizeCallback(ptr_, resize_la);
  glfwSetKeyCallback(ptr_, key_la);
}

void Window::resize_callback(GLFWwindow *p, int32 width, int32 height) {
  glViewport(0, 0, width, height);
  rdr_.cam_.htow = static_cast<float>(height) / static_cast<float>(width);
}

void Window::key_callback(GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods) {
  if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
    glfwSetWindowShouldClose(p, 1);
  if (key == GLFW_KEY_SPACE && act == GLFW_PRESS)
    std::cout << "Space pressed!!" << std::endl;
}
