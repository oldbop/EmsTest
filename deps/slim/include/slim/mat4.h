#ifndef SLIM_MAT4_H
#define SLIM_MAT4_H

#include "types.h"
#include "vec3.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

inline void mat4_print(const mat4 *m) {

  for (uint32_t i = 0; i < 4; ++i) {
    printf("%.1f %.1f %.1f %.1f\n", m->v[(4 * i)],
                                    m->v[(4 * i) + 1],
                                    m->v[(4 * i) + 2],
                                    m->v[(4 * i) + 3]);
  }

  printf("\n");
}

inline mat4 mat4_idy(void) {

  mat4 res = {
        1.0f,     0.0f,     0.0f,     0.0f,
        0.0f,     1.0f,     0.0f,     0.0f,
        0.0f,     0.0f,     1.0f,     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_tsp(const mat4 *m) {

  mat4 res;

  for (uint32_t i = 0; i < 4; ++i) {
    for (uint32_t j = 0; j < 4; ++j) {
      res.v[(4 * i) + j] = m->v[i + (4 * j)];
    }
  }

  return res;
}

inline mat4 mat4_add(const mat4 *m1, const mat4 *m2) {

  mat4 res;

  for (uint32_t i = 0; i < 16; ++i) {
    res.v[i] = m1->v[i] + m2->v[i];
  }

  return res;
}

inline mat4 mat4_sub(const mat4 *m1, const mat4 *m2) {

  mat4 res;

  for (uint32_t i = 0; i < 16; ++i) {
    res.v[i] = m1->v[i] - m2->v[i];
  }

  return res;
}

inline mat4 mat4_mul(const mat4 *m1, const mat4 *m2) {

  mat4 res = { 0 };

  for (uint32_t i = 0; i < 4; ++i) {
    for (uint32_t j = 0; j < 4; ++j) {
      for (uint32_t k = 0; k < 4; ++k) {
        res.v[(4 * i) + j] += m1->v[(4 * i) + k] * m2->v[j + (4 * k)];
      }
    }
  }

  return res;
}

inline mat4 mat4_scl(const vec3 *v) {

  mat4 res = {
     v->v[0],     0.0f,     0.0f,     0.0f,
        0.0f,  v->v[1],     0.0f,     0.0f,
        0.0f,     0.0f,  v->v[2],     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_tst(const vec3 *v) {

  mat4 res = {
        1.0f,     0.0f,     0.0f,  v->v[0],
        0.0f,     1.0f,     0.0f,  v->v[1],
        0.0f,     0.0f,     1.0f,  v->v[2],
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_rotX(float r) {

  float sin_r = sinf(r), cos_r = cosf(r);

  mat4 res = {
        1.0f,     0.0f,     0.0f,     0.0f,
        0.0f,    cos_r,   -sin_r,     0.0f,
        0.0f,    sin_r,    cos_r,     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_rotY(float r) {

  float sin_r = sinf(r), cos_r = cosf(r);

  mat4 res = {
       cos_r,     0.0f,    sin_r,     0.0f,
        0.0f,     1.0f,     0.0f,     0.0f,
      -sin_r,     0.0f,    cos_r,     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_rotZ(float r) {

  float sin_r = sinf(r), cos_r = cosf(r);

  mat4 res = {
       cos_r,   -sin_r,     0.0f,     0.0f,
       sin_r,    cos_r,     0.0f,     0.0f,
        0.0f,     0.0f,     1.0f,     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_lookat(const vec3 *eye, const vec3 *center, const vec3 *up) {

  vec3 d = vec3_sub(eye, center);
  d      = vec3_nor(&d);

  vec3 r = vec3_crs(up, &d);
  r      = vec3_nor(&r);

  vec3 u = vec3_crs(&d, &r);

  mat4 rot = {
      r.v[0],   r.v[1],   r.v[2],     0.0f,
      u.v[0],   u.v[1],   u.v[2],     0.0f,
      d.v[0],   d.v[1],   d.v[2],     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  vec3 inv_pos = { -eye->v[0], -eye->v[1], -eye->v[2] };
  mat4 tst     = mat4_tst(&inv_pos);

  mat4 res = mat4_mul(&rot, &tst);

  return res;

  /*
  mat4 res = {
      r.v[0],   r.v[1],   r.v[2],   - (r.v[0] * eye.v[0]) - (r.v[1] * eye.v[1]) - (r.v[2] * eye.v[2]),
      u.v[0],   u.v[1],   u.v[2],   - (u.v[0] * eye.v[0]) - (u.v[1] * eye.v[1]) - (u.v[2] * eye.v[2]),
      d.v[0],   d.v[1],   d.v[2],   - (d.v[0] * eye.v[0]) - (d.v[1] * eye.v[1]) - (d.v[2] * eye.v[2]),
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
  */

}



#ifdef __cplusplus
}
#endif

#endif
