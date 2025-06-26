#include "camera.hpp"

#include <slim/slim.h>

mat4 Camera::get_transform(uint32_t screen_width, uint32_t screen_height) const {

  float htow = (float) screen_height / (float) screen_width;

  mat4 view = mat4_lookat(&pos_, &tar_, &ort_);
  mat4 proj = mat4_persp_hor_fov(fovx_, htow, near_, far_);
  mat4 res  = mat4_mul(&proj, &view);

  return res;
}
