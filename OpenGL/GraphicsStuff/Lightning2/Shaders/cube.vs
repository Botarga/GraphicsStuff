#version 330 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 vertexNormal;
out vec3 vertexFragPosition;

void main()
{
	gl_Position = projection * view * model * vec4(vPosition, 1.0);
	vertexNormal = vNormal;
	vertexFragPosition = vec3(model * vec4(vPosition, 1.0));
}