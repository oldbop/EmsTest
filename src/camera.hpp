#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "integers.hpp"

#include <slim/slim.h>

class Camera {
public:
  mat4 get_transform(uint32 screen_width, uint32 screen_height) const;
  void set_aspect(float aspect) { asp_ = aspect; }

private:
  vec3 pos_ = { 0.0f, 0.0f, 2.0f };
  vec3 tar_ = { 0.0f, 0.0f, 0.0f };
  vec3 ort_ = { 0.0f, 1.0f, 0.0f };

  float fovx_ = PI / 2.0f;
  float near_ = 0.1f;
  float far_  = 100.0f;
  float asp_  = 1.0f;
};

#endif
