#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

const float amplitude = 0.033;   
const float amplitude2 = 0.5;
const float frequency = 1.3;      
const float PI = 3.14159;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{

    float distance = length(aPos);
    float mov2 = amplitude2 * sin( 2.0*PI * distance * frequency + time);
    float mov = amplitude * sin( 2.0*PI * distance * frequency + time);
     //BUENO
    gl_Position = projection * view * model * vec4(aPos.x+mov2, aPos.y+mov*mov, aPos.z+mov*mov, 1.0);
    

    // Puedes ajustar las coordenadas de textura según sea necesario
    TexCoords = vec2(aTexCoords.x, aTexCoords.y);
}
