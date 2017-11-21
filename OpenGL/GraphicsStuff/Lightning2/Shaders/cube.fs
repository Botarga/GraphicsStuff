#version 330 core

in vec3 vertexNormal;
in vec3 vertexFragPosition;

out vec4 FragColor;

uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main()
{
	// Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// Difuse
	vec3 Normal = normalize(vertexNormal);
	vec3 lightDir = normalize(vertexFragPosition - lightPosition);
	float diffuseFactor = max(dot(-lightDir, Normal), 0.0);
	vec3 diffuse = diffuseFactor * lightColor;

	// Specular
	vec3 reflectDir = normalize(reflect(lightDir, Normal));
	vec3 directionDir = normalize(cameraPosition - vertexFragPosition);

	float specularFactor = pow(max(dot(reflectDir, directionDir), 0.0), 32);
	vec3 specular = specularFactor * lightColor;

	vec3 result = (ambient + diffuse + specular) * cubeColor; 
	FragColor = vec4(result, 1.0);
}