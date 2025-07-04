#ifndef SLIM_VEC3_H
#define SLIM_VEC3_H

#include "types.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

inline void vec3_print(const vec3 *v) {
  printf("%.1f\n%.1f\n%.1f\n\n", v->v[0], v->v[1], v->v[2]);
}

inline vec3 vec3_nor(const vec3 *v) {

  float mag = sqrtf((v->v[0] * v->v[0]) +
                    (v->v[1] * v->v[1]) +
                    (v->v[2] * v->v[2]));

  float inv_mag = (mag == 0.0f) ? 0.0f : 1.0f / mag;

  vec3 res = {
    v->v[0] * inv_mag, 
    v->v[1] * inv_mag, 
    v->v[2] * inv_mag
  };

  return res;
}

inline float vec3_mag(const vec3 *v) {

  float res = sqrtf((v->v[0] * v->v[0]) +
                    (v->v[1] * v->v[1]) +
                    (v->v[2] * v->v[2]));

  return res;
}

inline float vec3_dot(const vec3 *v1, const vec3 *v2) {

  float res = (v1->v[0] * v2->v[0]) +
              (v1->v[1] * v2->v[1]) +
              (v1->v[2] * v2->v[2]);

  return res;
}

inline vec3 vec3_crs(const vec3 *v1, const vec3 *v2) {

  vec3 res = {
    (v1->v[1] * v2->v[2]) - (v1->v[2] * v2->v[1]),
    (v1->v[2] * v2->v[0]) - (v1->v[0] * v2->v[2]),
    (v1->v[0] * v2->v[1]) - (v1->v[1] * v2->v[0])
  };

  return res;
}

inline vec3 vec3_add(const vec3 *v1, const vec3 *v2) {

  vec3 res = {
    v1->v[0] + v2->v[0],
    v1->v[1] + v2->v[1],
    v1->v[2] + v2->v[2]
  };

  return res;
}

inline vec3 vec3_sub(const vec3 *v1, const vec3 *v2) {

  vec3 res = {
    v1->v[0] - v2->v[0],
    v1->v[1] - v2->v[1],
    v1->v[2] - v2->v[2]
  };

  return res;
}

inline vec3 vec3_sml(const vec3 *v, float scalar) {

  vec3 res = {
    v->v[0] * scalar,
    v->v[1] * scalar,
    v->v[2] * scalar
  };

  return res;
}

#ifdef __cplusplus
}
#endif

#endif
