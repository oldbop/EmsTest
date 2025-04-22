#include "camera.hpp"

#include <slim/slim.h>

mat4 Camera::get_transform() const {

  // Make the lookat and perspective projection matrices part of the maths library

  vec3 d = vec3_sub(&pos_, &tar_);
  d      = vec3_nor(&d);

  vec3 r = vec3_crs(&ori_, &d);
  r      = vec3_nor(&r);

  vec3 u = vec3_crs(&d, &r);

  mat4 rot = {
      r.v[0],   r.v[1],   r.v[2],     0.0f,
      u.v[0],   u.v[1],   u.v[2],     0.0f,
      d.v[0],   d.v[1],   d.v[2],     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  vec3 inv_pos = { -pos_.v[0], -pos_.v[1], -pos_.v[2] };
  mat4 tst     = mat4_tst(&inv_pos);

  mat4 res = mat4_mul(&rot, &tst);

  return res;

  /*
  mat4 res = {
      r.v[0],   r.v[1],   r.v[2],   - (r.v[0] * pos_.v[0]) - (r.v[1] * pos_.v[1]) - (r.v[2] * pos_.v[2]),
      u.v[0],   u.v[1],   u.v[2],   - (u.v[0] * pos_.v[0]) - (u.v[1] * pos_.v[1]) - (u.v[2] * pos_.v[2]),
      d.v[0],   d.v[1],   d.v[2],   - (d.v[0] * pos_.v[0]) - (d.v[1] * pos_.v[1]) - (d.v[2] * pos_.v[2]),
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
  */
}
