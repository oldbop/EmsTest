#ifndef SLIM_MAT4_H
#define SLIM_MAT4_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void mat4_print(float *m);
void mat4_idy(float *m);
void mat4_tsp(float *m);
void mat4_add(float *m1, float *m2);
void mat4_sub(float *m1, float *m2);
void mat4_mul(float *m1, float *m2);
void mat4_scl(float *m, float *v);
void mat4_tst(float *m, float *v);
void mat4_rotX(float *m, float r);
void mat4_rotY(float *m, float r);
void mat4_rotZ(float *m, float r);

#ifdef __cplusplus
}
#endif

#endif
