#ifndef SLIM_MAT4_H
#define SLIM_MAT4_H

#include "types.h"

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

#ifdef __cplusplus
}
#endif

#endif
