#include "camera.hpp"

#include <slim/slim.h>

mat4 Camera::get_transform() const {

  mat4 view = mat4_lookat(&pos, &tar, &ort);
  mat4 proj = mat4_persp_hor_fov(fovx, htow, near, far);
  mat4 res  = mat4_mul(&proj, &view);

  return res;
}
