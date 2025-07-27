#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "integers.hpp"

#include <slim/slim.h>

struct Camera {

  mat4 get_transform(int32 width, int32 height) const;

  vec3  pos;
  vec3  tar;
  vec3  ort;

  float fovx;
  float near;
  float far;
};

#endif
