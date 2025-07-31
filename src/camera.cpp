#include "camera.hpp"
#include "integers.hpp"

#include <slim/slim.h>

mat4 Camera::get_transform(int32 width, int32 height) const {

  float htow = static_cast<float>(height) / static_cast<float>(width);

  mat4 view = mat4_lookat(&pos, &tar, &ort);
  mat4 proj = mat4_persp_hor_fov(fovx, htow, near, far);

  return mat4_mul(&proj, &view);
}
