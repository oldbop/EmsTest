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
    printf("%.1f %.1f %.1f %.1f\n", m->v[i],
                                    m->v[i +  4],
                                    m->v[i +  8],
                                    m->v[i + 12]);
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
      res.v[i + (4 * j)] = m->v[(4 * i) + j];
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
        res.v[i + (4 * j)] += m1->v[i + (4 * k)] * m2->v[(4 * j) + k];
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
        1.0f,     0.0f,     0.0f,     0.0f,
        0.0f,     1.0f,     0.0f,     0.0f,
        0.0f,     0.0f,     1.0f,     0.0f,
     v->v[0],  v->v[1],  v->v[2],     1.0f
  };

  return res;
}

inline mat4 mat4_rotX(float r) {

  float sin_r = sinf(r), cos_r = cosf(r);

  mat4 res = {
        1.0f,     0.0f,     0.0f,     0.0f,
        0.0f,    cos_r,    sin_r,     0.0f,
        0.0f,   -sin_r,    cos_r,     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_rotY(float r) {

  float sin_r = sinf(r), cos_r = cosf(r);

  mat4 res = {
       cos_r,     0.0f,   -sin_r,     0.0f,
        0.0f,     1.0f,     0.0f,     0.0f,
       sin_r,     0.0f,    cos_r,     0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
  };

  return res;
}

inline mat4 mat4_rotZ(float r) {

  float sin_r = sinf(r), cos_r = cosf(r);

  mat4 res = {
       cos_r,    sin_r,     0.0f,     0.0f,
      -sin_r,    cos_r,     0.0f,     0.0f,
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

  vec3 inv_pos = { -eye->v[0], -eye->v[1], -eye->v[2] };

  float tx = vec3_dot(&r, &inv_pos);
  float ty = vec3_dot(&u, &inv_pos);
  float tz = vec3_dot(&d, &inv_pos);

  mat4 res = {
      r.v[0],   u.v[0],   d.v[0],     0.0f,
      r.v[1],   u.v[1],   d.v[1],     0.0f,
      r.v[2],   u.v[2],   d.v[2],     0.0f,
          tx,       ty,       tz,     1.0f
  };

  return res;
}

inline mat4 mat4_persp_hor_fov(float fovx, float htow, float n, float f) {

  float r = n * tanf(fovx / 2.0f);
  float l = -r;
  float t = htow * r;
  float b = -t;

  mat4 res = { 0 };

  res.v[0]  =  (2 * n) / (r - l);
  res.v[5]  =  (2 * n) / (t - b);
  res.v[8]  =  (r + l) / (r - l);
  res.v[9]  =  (t + b) / (t - b);
  res.v[10] = -(f + n) / (f - n);
  res.v[11] = -1.0f;
  res.v[14] = -(2 * f * n) / (f - n);

  return res;
}

inline mat4 mat4_persp_ver_fov(float fovy, float wtoh, float n, float f) {

  float t = n * tanf(fovy / 2.0f);
  float b = -t;
  float r = wtoh * t;
  float l = -r;

  mat4 res = { 0 };

  res.v[0]  =  (2 * n) / (r - l);
  res.v[5]  =  (2 * n) / (t - b);
  res.v[8]  =  (r + l) / (r - l);
  res.v[9]  =  (t + b) / (t - b);
  res.v[10] = -(f + n) / (f - n);
  res.v[11] = -1.0f;
  res.v[14] = -(2 * f * n) / (f - n);

  return res;
}

#ifdef __cplusplus
}
#endif

#endif
