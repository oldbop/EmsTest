#ifndef SLIM_VEC3_H
#define SLIM_VEC3_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void  vec3_print(const vec3 *v);
vec3  vec3_nor(const vec3 *v);
float vec3_mag(const vec3 *v);
float vec3_dot(const vec3 *v1, const vec3 *v2);
vec3  vec3_crs(const vec3 *v1, const vec3 *v2);
vec3  vec3_add(const vec3 *v1, const vec3 *v2);
vec3  vec3_sub(const vec3 *v1, const vec3 *v2);
vec3  vec3_sml(const vec3 *v, float scalar);

#ifdef __cplusplus
}
#endif

#endif
