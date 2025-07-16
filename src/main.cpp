#include "camera.hpp"
#include "integers.hpp"
#include "shader_program.hpp"
#include "window.hpp"

#include "util/file_handling.hpp"

#ifdef SYS_GL_HEADERS
#include <GL/gl.h>
#include <GL/glext.h>

#else
#include <glad/gl.h>

#endif

#ifdef EMSCRIPTEN
#include <emscripten.h>

#endif

#include <GLFW/glfw3.h>

#include <slim/slim.h>

#include <cmath>
#include <iostream>
#include <optional>
#include <string>

int main(int argc, char **argv) {

  std::optional<Window> opt = Window::create(700, 700, "Rotating cube");

  if (!opt.has_value())
    return -1;

  Window window(std::move(*opt));

  while (!window.should_close())
    window.draw();

  return 0;
}
