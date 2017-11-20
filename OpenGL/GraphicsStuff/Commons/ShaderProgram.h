#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <utility>

class ShaderProgram
{
public:

	ShaderProgram(std::vector<std::pair<const char*, int>> shaders)
	{

	}

	void Use()
	{

	}

	void SetInt(const char* name, int value)
	{

	}

	void SetMat4(const char* name, const glm::mat4& value)
	{

	}
};