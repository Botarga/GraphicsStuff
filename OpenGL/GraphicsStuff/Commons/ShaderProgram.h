#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>
#include <utility>
#include <sstream>
#include <fstream>
#include <iostream>

class ShaderProgram
{
private:
	GLuint mId;

public:

	ShaderProgram(std::vector<std::pair<const char*, int>> shaders)
	{
		mId = glCreateProgram();

		std::vector<GLuint> shaderIds(shaders.size());
		int cont = 0;
		for (const auto& s : shaders) {
			std::ifstream shaderFile(s.first);
			std::string codeStr((std::istreambuf_iterator<char>(shaderFile)),
				(std::istreambuf_iterator<char>()));
			const char* shaderCode = codeStr.c_str();
			shaderIds[cont] = CompileShader(shaderCode, s.second);
			glAttachShader(mId, shaderIds[cont++]);
		}

		glLinkProgram(mId);
		GLint success;
		glGetProgramiv(mId, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &success);
			char* message = new char[success];
			glGetProgramInfoLog(mId, success, 0, message);
			std::cerr << "PROGRAM_LINK_ERROr:" << message << std::endl;
			delete[] message;
		}

		for (const auto& id : shaderIds) {
			glDetachShader(mId, id);
			glDeleteShader(id);
		}
	}

	GLuint CompileShader(const char* code, int type) {
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &code, 0);
		glCompileShader(shader);
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			switch (type) {
			case GL_VERTEX_SHADER:
				std::cerr << "VERTEX_SHADER_ERROR::";
				break;
			case GL_FRAGMENT_SHADER:
				std::cerr << "FRAGMENT_SHADER_ERROR::";
				break;
			case GL_GEOMETRY_SHADER:
				std::cerr << "GEOMETRY_SHADER_ERROR::";
				break;

			}
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &success);
			char* message = new char[success];
			glGetShaderInfoLog(shader, success, 0, message);
			std::cerr << "COMPILE_ERROR:" << message << std::endl;
			delete[] message;
		}

		return shader;
	}

	void Use()
	{
		glUseProgram(mId);
	}

	void SetInt(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(mId, name), value);
	}

	void SetMat4(const char* name, const glm::mat4& value)
	{
		glUniformMatrix4fv(glGetUniformLocation(mId, name), 1, false, glm::value_ptr(value));
	}

	void SetVec3(const char* name, const glm::vec3& value)
	{
		glUniform3fv(glGetUniformLocation(mId, name), 1, &value[0]);
	}

	void SetFloat(const char* name, float value) {
		glUniform1f(glGetUniformLocation(mId, name), value);
	}
};