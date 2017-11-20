#version 330 core
layout (location = 0) in vec3 vPosition;

out vec4 vertexColor;

uniform vec3 vColor;
uniform vec3 lampColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model *vec4(vPosition, 1.0);
	vertexColor = vec4(vColor, 1.0) * vec4(lampColor, 1.0);
}