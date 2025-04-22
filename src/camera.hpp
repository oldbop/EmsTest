#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <slim/slim.h>

class Camera {
public:
  mat4 get_transform() const;

private:
  vec3 tar_ = { 0.0f, 0.0f, 0.0f };
  vec3 pos_ = { 0.0f, 0.0f, 3.0f };
  vec3 ori_ = { 0.0f, 1.0f, 0.0f };
};


#endif
