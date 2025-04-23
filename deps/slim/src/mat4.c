#include <slim/mat4.h>

#ifdef __cplusplus
extern "C" {
#endif

void mat4_print(const mat4 *m);
mat4 mat4_idy(void);
mat4 mat4_tsp(const mat4 *m);
mat4 mat4_add(const mat4 *m1, const mat4 *m2);
mat4 mat4_sub(const mat4 *m1, const mat4 *m2);
mat4 mat4_mul(const mat4 *m1, const mat4 *m2);
mat4 mat4_scl(const vec3 *v);
mat4 mat4_tst(const vec3 *v);
mat4 mat4_rotX(float r);
mat4 mat4_rotY(float r);
mat4 mat4_rotZ(float r);
mat4 mat4_lookat(const vec3 *eye, const vec3 *center, const vec3 *up);

#ifdef __cplusplus
}
#endif
