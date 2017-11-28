#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

uniform vec3 camPosition;

out vec4 FragColor;

in vec3 vertexFragPosition;
in vec3 vertexNormal;


void main()
{
	// Ambient
	vec3 ambient = material.ambient * light.ambient;

	// Diffuse
	vec3 lightDir = normalize(vertexFragPosition - light.position);
	vec3 Normal = normalize(vertexNormal);
	float diffuseFactor = max(dot(-lightDir, Normal), 0.0);

	vec3 diffuse = diffuseFactor * material.diffuse * light.diffuse;
	// Specular
	vec3 reflection = normalize(reflect(lightDir, Normal));
	vec3 viewDir = normalize(camPosition - vertexFragPosition);
	float specularFactor = pow(max(dot(reflection, viewDir), 0.0), material.shininess);
	vec3 specular =  specularFactor * material.specular * light.specular;

	// Result
	vec3 result = (ambient + diffuse + specular);
	FragColor = vec4(result, 1.0);
}