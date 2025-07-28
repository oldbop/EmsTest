#include "camera.hpp"
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

struct Context {
  Window&   window;
  Renderer& rdr;
};

void loop(void *ptr) {

  Context ctx = *static_cast<Context *>(ptr);

  float time = ctx.window.time();

  ctx.rdr.render(time, ctx.window.width(), ctx.window.height());

  ctx.window.swap_buffers();
  ctx.window.poll_events();
}

int main(int argc, char **argv) {

  std::optional<Window> opt = Window::create(700, 700, "Rotating cube");

  if (!opt.has_value())
    return -1;

  Window window(std::move(*opt));
  opt.reset();

  Mesh mesh;

  ShaderProgram prog;

  std::string vert = load_file("res/shaders/square.vert");
  std::string frag = load_file("res/shaders/square.frag");

  prog.compile_shader(GL_VERTEX_SHADER, vert);
  prog.compile_shader(GL_FRAGMENT_SHADER, frag);
  prog.create_program();

  Camera cam = {
    { 0.0f, 0.0f, 4.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },
    PI / 3.0f,
    0.1f,
    100.0f
  };

  Renderer rdr(std::move(mesh), std::move(prog), cam);

  Context ctx = { window, rdr };

#ifdef EMSCRIPTEN
  emscripten_set_main_loop_arg(loop, &ctx, 0, true);
#else
  while (!window.should_close())
    loop(&ctx);
#endif

  return 0;
}
