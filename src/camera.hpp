#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <slim/slim.h>

struct Camera {

  mat4 get_transform() const;

  vec3 pos = { 0.0f, 0.0f, 2.0f };
  vec3 tar = { 0.0f, 0.0f, 0.0f };
  vec3 ort = { 0.0f, 1.0f, 0.0f };

  float fovx = PI / 3.0f;
  float htow = 1.0f;
  float near = 0.1f;
  float far  = 100.0f;
};

#endif
