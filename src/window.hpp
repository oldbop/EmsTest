#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "camera.hpp"
#include "integers.hpp"

#include <GLFW/glfw3.h>

#include <optional>
#include <string>

class Window {
public:
  ~Window();
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&& other) noexcept;
  Window& operator=(Window&& other) = delete;

  static std::optional<Window> create(int32 width, int32 height, const std::string& title);

  bool should_close() const { return glfwWindowShouldClose(ptr_); }
  void run();
private:
  void register_callbacks();

  void resize_callback(GLFWwindow *p, int32 width, int32 height);
  void key_callback(GLFWwindow *p, int32 key, int32 scan, int32 act, int32 mods);

  Camera cam_;
  GLFWwindow *ptr_ = nullptr;

  Window() = default;
};

#endif
