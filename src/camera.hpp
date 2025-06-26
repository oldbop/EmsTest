#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <slim/slim.h>

#include <cstdint>

class Camera {
public:
  mat4 get_transform(uint32_t screen_width, uint32_t screen_height) const;

private:
  vec3 pos_ = { 0.0f, 0.0f, 2.0f };
  vec3 tar_ = { 0.0f, 0.0f, 0.0f };
  vec3 ort_ = { 0.0f, 1.0f, 0.0f };

  float fovx_ = PI / 2.0f;
  float near_ = 0.1f;
  float far_  = 100.0f;
};

#endif
