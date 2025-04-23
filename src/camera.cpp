#include "camera.hpp"

#include <slim/slim.h>

mat4 Camera::get_transform() const {

  mat4 view = mat4_lookat(&pos_, &tar_, &ort_);

  return view;
}
