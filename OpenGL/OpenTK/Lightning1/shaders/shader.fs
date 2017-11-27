#version 330 core

uniform vec3 cubeColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 camPosition;

out vec4 FragColor;

in vec3 vertexFragPosition;
in vec3 vertexNormal;


void main()
{
	// Ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 lightDir = normalize(vertexFragPosition - lightPosition);
	vec3 Normal = normalize(vertexNormal);
	float diffuseFactor = max(dot(-lightDir, Normal), 0.0);

	vec3 diffuse = diffuseFactor * lightColor;
	// Specular
	vec3 reflection = normalize(reflect(lightDir, Normal));
	vec3 viewDir = normalize(camPosition - vertexFragPosition);
	float specularFactor = pow(max(dot(reflection, viewDir), 0.0), 32);
	vec3 specular =  specularFactor * lightColor;

	// Result
	vec3 result = (ambient + diffuse + specular) * cubeColor;
	FragColor = vec4(result, 1.0);
}