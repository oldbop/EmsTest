#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "integers.hpp"

#include <GLFW/glfw3.h>

#include <optional>
#include <string>
#include <utility>

class Window {
public:
  ~Window();
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&& other) noexcept;
  Window& operator=(Window&& other) = delete;

  static std::optional<Window> create(int32 width, int32 height, const std::string& title);

  bool  should_close() const { return glfwWindowShouldClose(ptr_); }
  float time() const { return glfwGetTime(); }

  int32 width() const { return width_; }
  int32 height() const { return height_; }

  void swap_buffers() { glfwSwapBuffers(ptr_); }
  void poll_events() { glfwPollEvents(); }
private:
  void register_callbacks();

  void key_callback(GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods);
  void resize_callback(GLFWwindow *p, int32 width, int32 height);

  GLFWwindow *ptr_ = nullptr;

  int32 width_  = 0;
  int32 height_ = 0;

  Window() = default;

  void swap(Window& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(width_, other.width_);
    std::swap(height_, other.height_);
  }
};

#endif
