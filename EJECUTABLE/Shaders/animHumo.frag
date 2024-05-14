#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D texture1;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

out vec4 color;
uniform int activaTransparencia;
uniform vec4 colorAlpha;

uniform Material material;



void main()
{
 
  

    color = vec4(colorAlpha)*vec4( 1,texture(material.diffuse, TexCoords).rgb );
	  if(color.a < 0.1 && activaTransparencia==1)
        discard;
}


//vec4 texColor= texture(texture1,TexCoords);
    //if(texColor.a < 0.1)
       // discard;
    //FragColor = texColor;