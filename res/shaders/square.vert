#version ${GLSL_VERSION}

layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aCol;

uniform mat4 Rot;

//out vec3 fCol;

void main() {
  gl_Position = Rot * vec4(aPos, 1.0);
  //fCol = aCol;
}
