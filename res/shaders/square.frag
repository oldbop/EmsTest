#version ${GLSL_VERSION}

precision highp float;

in vec3 fCol;
out vec4 rCol;

void main() {
  rCol = vec4(fCol, 1.0);
}
