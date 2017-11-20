#pragma once
#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
class Camera
{
private:
	glm::mat4 viewMatrix;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float yaw, pitch;
	double lastX, lastY;
	bool firstMouse = true;
	float cameraSpeed = 8.0f;
	float sensitivity = 0.5f;

public:
	enum MoveType{FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN};

	Camera(glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) : 
		cameraPos{ pos }, cameraFront{ front }, cameraUp{ up }, yaw{ yaw }, pitch{pitch}
	{

		viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void proccess_input(MoveType type, double deltaTime, bool sprint)
	{
		float speed = cameraSpeed * deltaTime;
		if (sprint)
			speed += speed;

		switch (type)
		{
		case MoveType::FORWARD:
			cameraPos += cameraFront * speed;
			break;
		case MoveType::BACKWARD:
			cameraPos -= cameraFront * speed;
			break;
		case MoveType::LEFT:
			cameraPos += glm::normalize(glm::cross(cameraUp, cameraFront)) * speed;
			break;
		case MoveType::RIGHT:
			cameraPos -= glm::normalize(glm::cross(cameraUp, cameraFront)) * speed;
			break;
		case MoveType::UP:
			cameraPos += cameraUp * speed;
			break;
		case MoveType::DOWN:
			cameraPos -= cameraUp * speed;
			break;

		}

		viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	void proccess_mouse(double deltaTime, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		float sensitivity = 0.05;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);
		viewMatrix = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	}

	glm::mat4 GetViewMatrix()
	{
		return viewMatrix;
	}

};