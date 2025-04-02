#include <slim/vec4.h>

#ifdef __cplusplus
extern "C" {
#endif

void  vec4_print(const vec4 *v);
vec4  vec4_nor(const vec4 *v);
float vec4_mag(const vec4 *v);
float vec4_dot(const vec4 *v1, const vec4 *v2);
vec4  vec4_add(const vec4 *v1, const vec4 *v2);
vec4  vec4_sub(const vec4 *v1, const vec4 *v2);
vec4  vec4_sml(const vec4 *v, float scalar);

#ifdef __cplusplus
}
#endif
