#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "integers.hpp"

#include <GLFW/glfw3.h>

#include <memory>
#include <string>

template<typename T>
struct Size {
  T width;
  T height;
};

class Window {
public:
  Window(int32 width, int32 height, const std::string& title);

  Size<int32> get_size() const;
  std::string get_title() const;
private:
  void resize_cb(GLFWwindow *win, int32 width, int32 height);
  void key_cb(GLFWwindow *win, int32 key, int32 scan, int32 act, int32 mods);

  std::unique_ptr<GLFWwindow, void (*)(GLFWwindow *)> ptr_;
};

#endif
