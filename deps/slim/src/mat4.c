#include <slim/mat4.h>

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void mat4_print(float *m) {

  for (uint32_t i = 0; i < 16; ++i) {

    printf("%.1f ", m[i]);

    if ((i + 1) % 4 == 0) {
      printf("\n");
    }
  }

  printf("\n");
}

void mat4_idy(float *m) {

  mat4 result = {
      1.0f,   0.0f,   0.0f,   0.0f,
      0.0f,   1.0f,   0.0f,   0.0f,
      0.0f,   0.0f,   1.0f,   0.0f,
      0.0f,   0.0f,   0.0f,   1.0f
  };

  memcpy(m, result, 16 * sizeof(float));
}

void mat4_tsp(float *m) {

  mat4 wm;
  memcpy(wm, m, 16 * sizeof(float));

  for (uint32_t i = 0; i < 4; ++i) {
    for (uint32_t j = 0; j < 4; ++j) {
      m[(4 * i) + j] = wm[i + (4 * j)];
    }
  }
}

void mat4_add(float *m1, float *m2) {

  mat4 wm1;
  memcpy(wm1, m1, 16 * sizeof(float));

  for (uint32_t i = 0; i < 16; ++i) {
    m1[i] = wm1[i] + m2[i];
  }
}

void mat4_sub(float *m1, float *m2) {

  mat4 wm1;
  memcpy(wm1, m1, 16 * sizeof(float));

  for (uint32_t i = 0; i < 16; ++i) {
    m1[i] = wm1[i] - m2[i];
  }
}

void mat4_mul(float *m1, float *m2) {

  mat4 wm1;

  memcpy(wm1, m1, 16 * sizeof(float));
  memset(m1,   0, 16 * sizeof(float));

  for (uint32_t i = 0; i < 4; ++i) {
    for (uint32_t j = 0; j < 4; ++j) {
      for (uint32_t k = 0; k < 4; ++k) {
        m1[(4 * i) + j] += wm1[(4 * i) + k] * m2[j + (4 * k)];
      }
    }
  }
}

void mat4_scl(float *m, float *v) {

  mat4 result = {
      v[0],   0.0f,   0.0f,   0.0f,
      0.0f,   v[1],   0.0f,   0.0f,
      0.0f,   0.0f,   v[2],   0.0f,
      0.0f,   0.0f,   0.0f,   1.0f
  };

  memcpy(m, result, 16 * sizeof(float));
}

void mat4_tst(float *m, float *v) {

  mat4 result = {
      1.0f,   0.0f,   0.0f,   v[0],
      0.0f,   1.0f,   0.0f,   v[1],
      0.0f,   0.0f,   1.0f,   v[2],
      0.0f,   0.0f,   0.0f,   1.0f
  };

  memcpy(m, result, 16 * sizeof(float));
}

void mat4_rotX(float *m, float r) {

  float sin_r = sin(r), cos_r = cos(r);

  mat4 result = {
      1.0f,   0.0f,   0.0f,   0.0f,
      0.0f,  cos_r, -sin_r,   0.0f,
      0.0f,  sin_r,  cos_r,   0.0f,
      0.0f,   0.0f,   0.0f,   1.0f
  };

  memcpy(m, result, 16 * sizeof(float));
}

void mat4_rotY(float *m, float r) {

  float sin_r = sin(r), cos_r = cos(r);

  mat4 result = {
     cos_r,   0.0f,  sin_r,   0.0f,
      0.0f,   1.0f,   0.0f,   0.0f,
    -sin_r,   0.0f,  cos_r,   0.0f,
      0.0f,   0.0f,   0.0f,   1.0f
  };

  memcpy(m, result, 16 * sizeof(float));
}

void mat4_rotZ(float *m, float r) {

  float sin_r = sin(r), cos_r = cos(r);

  mat4 result = {
     cos_r, -sin_r,   0.0f,   0.0f,
     sin_r,  cos_r,   0.0f,   0.0f,
      0.0f,   0.0f,   1.0f,   0.0f,
      0.0f,   0.0f,   0.0f,   1.0f
  };

  memcpy(m, result, 16 * sizeof(float));
}
