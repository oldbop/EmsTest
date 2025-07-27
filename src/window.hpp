#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "integers.hpp"

#include <GLFW/glfw3.h>

#include <optional>
#include <string>

struct Size {
  int32 width;
  int32 height;
};

class Window {
public:
  ~Window();
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&& other) noexcept;
  Window& operator=(Window&& other) = delete;

  static std::optional<Window> create(int32 width, int32 height, const std::string& title);

  bool should_close() const { return glfwWindowShouldClose(ptr_); }
  float time() const { return glfwGetTime(); }
  Size size() const;

  void swap_buffers() { glfwSwapBuffers(ptr_); }
  void poll_events() { glfwPollEvents(); }
private:
  void register_callbacks();

  void key_callback(GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods);

  GLFWwindow *ptr_ = nullptr;

  Window() = default;
};

#endif
