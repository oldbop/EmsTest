#include "camera.hpp"
#include "integers.hpp"
#include "mesh.hpp"
#include "renderer.hpp"
#include "shader_program.hpp"
#include "window.hpp"

#include "util/file_handling.hpp"

#ifdef EMSCRIPTEN
#include <emscripten.h>

#endif

#include <optional>
#include <string>

int main(int argc, char **argv) {

  std::optional<Window> opt = Window::create(700, 700, "Rotating cube");

  if (!opt.has_value())
    return -1;

  Window window(std::move(*opt));
  opt.reset();

  std::string vert = load_file("res/shaders/square.vert");
  std::string frag = load_file("res/shaders/square.frag");

  ShaderProgram prog;

  prog.compile_shader(GL_VERTEX_SHADER, vert);
  prog.compile_shader(GL_FRAGMENT_SHADER, frag);
  prog.create_program();

  Mesh mesh;
  Camera cam;

  Renderer rdr(window, std::move(mesh), std::move(prog), cam);

  while (!window.should_close()) {

    float time = window.time();

    rdr.render(time);

    window.swap_buffers();
    window.poll_events();
  }

  return 0;
}
