#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

const float amplitude = 0.05;   
const float amplitude2 = 3.7;
const float frequency = 4.9;   
const float PI = 3.14159;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{

    float distance = length(aPos);
    //float estatica = amplitude * sin( 2.0*PI * distance * frequency + time);
    float estatica = amplitude * sin( 2.0*PI * distance * frequency + time);
  

     
     

    
     //BUENO
    gl_Position = projection * view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    

    // Puedes ajustar las coordenadas de textura según sea necesario
    TexCoords = vec2(aTexCoords.x+estatica, aTexCoords.y+estatica);
}
