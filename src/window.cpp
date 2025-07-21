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
  : cam_(std::move(other.cam_))
  , ptr_(std::exchange(other.ptr_, nullptr)) {

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

  Window window;

  window.ptr_ = window_ptr;

  glfwMakeContextCurrent(window.ptr_);
  glfwSwapInterval(1);

#ifndef SYS_GL_HEADERS
  gladLoadGL(glfwGetProcAddress);
#endif

  int32 fb_width, fb_height;

  glfwGetFramebufferSize(window.ptr_, &fb_width, &fb_height);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glViewport(0, 0, fb_width, fb_height);

  window.cam_.set_aspect(static_cast<float>(fb_width) / static_cast<float>(fb_height));

  return std::optional<Window>(std::move(window));
}

void Window::run() {

  glClear(GL_COLOR_BUFFER_BIT);
  
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
  cam_.set_aspect(static_cast<float>(width) / static_cast<float>(height));
}

void Window::key_callback(GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods) {
  if (key == GLFW_KEY_ESCAPE && act == GLFW_PRESS)
    glfwSetWindowShouldClose(p, 1);
  if (key == GLFW_KEY_SPACE && act == GLFW_PRESS)
    std::cout << "Space pressed!!" << std::endl;
}
