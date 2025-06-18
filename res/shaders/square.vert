#version ${GLSL_VERSION}

layout(location = 0) in vec3 aPos;

uniform mat4 M;
uniform mat4 V;

void main() {
  gl_Position = V * M * vec4(aPos, 1.0);
}
