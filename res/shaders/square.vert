#version ${GLSL_VERSION}

layout(location = 0) in vec3 aPos;

uniform mat4 M;
uniform mat4 PV;

void main() {
  gl_Position = PV * M * vec4(aPos, 1.0);
}
