#version 330 core

out vec4 fragColor;

in vec4 vertexColor;
in vec2 vertexTexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	fragColor = mix(texture(texture1, vertexTexCoord), texture(texture2, vertexTexCoord), 0.6) * vertexColor;
}