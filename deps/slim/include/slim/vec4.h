#ifndef SLIM_VEC4_H
#define SLIM_VEC4_H

#include "types.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

inline void vec4_print(const vec4 *v) {
  printf("%.1f %.1f %.1f %.1f\n", v->v[0], v->v[1], v->v[2], v->v[3]);
}

inline vec4 vec4_nor(const vec4 *v) {

  float mag = sqrtf((v->v[0] * v->v[0]) +
                    (v->v[1] * v->v[1]) +
                    (v->v[2] * v->v[2]) +
                    (v->v[3] * v->v[3]));

  float inv_mag = (mag == 0.0f) ? 0.0f : 1.0f / mag;

  vec4 res = {
    v->v[0] * inv_mag, 
    v->v[1] * inv_mag, 
    v->v[2] * inv_mag, 
    v->v[3] * inv_mag
  };

  return res;
}

inline float vec4_mag(const vec4 *v) {

  float res = sqrtf((v->v[0] * v->v[0]) +
                    (v->v[1] * v->v[1]) +
                    (v->v[2] * v->v[2]) +
                    (v->v[3] * v->v[3]));

  return res;
}

inline float vec4_dot(const vec4 *v1, const vec4 *v2) {

  float res = (v1->v[0] * v2->v[0]) +
              (v1->v[1] * v2->v[1]) +
              (v1->v[2] * v2->v[2]) +
              (v1->v[3] * v2->v[3]);

  return res;
}

inline vec4 vec4_add(const vec4 *v1, const vec4 *v2) {

  vec4 res = {
    v1->v[0] + v2->v[0],
    v1->v[1] + v2->v[1],
    v1->v[2] + v2->v[2],
    v1->v[3] + v2->v[3]
  };

  return res;
}

inline vec4 vec4_sub(const vec4 *v1, const vec4 *v2) {

  vec4 res = {
    v1->v[0] - v2->v[0],
    v1->v[1] - v2->v[1],
    v1->v[2] - v2->v[2],
    v1->v[3] - v2->v[3]
  };

  return res;
}

inline vec4 vec4_sml(const vec4 *v, float scalar) {

  vec4 res = {
    v->v[0] * scalar,
    v->v[1] * scalar,
    v->v[2] * scalar,
    v->v[3] * scalar
  };

  return res;
}

#ifdef __cplusplus
}
#endif

#endif
