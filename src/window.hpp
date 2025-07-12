#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "camera.hpp"
#include "integers.hpp"

#include <GLFW/glfw3.h>

#include <memory>
#include <string>

class Window {
public:
  Window() : ptr_(nullptr, nullptr) {}
  bool init(int32 width, int32 height, const std::string& title);
private:
  void resize_cb(GLFWwindow *win, int32 width, int32 height);
  void key_cb(GLFWwindow *win, int32 key, int32 scan, int32 act, int32 mods);

  Camera cam_;
  std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> ptr_;
};

#endif
