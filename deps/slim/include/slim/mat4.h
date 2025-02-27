#ifndef SLIM_MAT4_H
#define SLIM_MAT4_H

#ifdef __cplusplus
extern "C" {
#endif

typedef float mat4[16];

void mat4_idety(float *m);
void mat4_print(float *m);
void mat4_tsp(float *m);
void mat4_add(float *m1, float *m2);
void mat4_sub(float *m1, float *m2);
void mat4_mul(float *m1, float *m2);
void mat4_rotX(float *m, float r);
void mat4_rotY(float *m, float r);
void mat4_rotZ(float *m, float r);

#ifdef __cplusplus
}
#endif

#endif
