#version 330 core

out vec4 fragColor;
in vec3 vertexNormal;
in vec3 fragPos;

uniform vec3 lampColor;
uniform vec3 vertexColor;
uniform vec3 lightPos;

void main()
{
	float ambientLight = 0.1;
	vec3 ambient = ambientLight * lampColor;
	
	vec3 norm = normalize(vertexNormal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lampColor;

	vec3 result = (ambient + diffuse) * vertexColor;
	fragColor = vec4(result, 1.0);
}