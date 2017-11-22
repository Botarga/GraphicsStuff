#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

uniform float time;
void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords) * vec4(TexCoords, sin(time), 1.0);
}