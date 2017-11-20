#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class Camera
{
private:
	glm::mat4 viewMatrix;

public:
	enum MoveType{FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN};

	Camera()
	{

	}

	void proccess_input(MoveType type, double deltaTime, bool sprint)
	{
	}

	void proccess_mouse(double deltaTime, double x, double y)
	{

	}

	glm::mat4 GetViewMatrix()
	{
		return viewMatrix;
	}

};