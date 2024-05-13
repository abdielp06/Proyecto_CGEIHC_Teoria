#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

const float amplitudeX = 0.2;
const float amplitudeZ = 0.1;
const float frequencyX = 1.0;
const float frequencyZ = 2.5;
const float PI = 3.14159;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{
  float effectX = amplitudeX * sin(2.0 * PI * frequencyX * time);
  float effectZ = amplitudeZ * sin(2.0 * PI * frequencyZ * time);
  gl_Position = projection * view * model * vec4(aPos.x + effectX, aPos.y, aPos.z + effectZ, 1.0);
  TexCoords = aTexCoords;
}
