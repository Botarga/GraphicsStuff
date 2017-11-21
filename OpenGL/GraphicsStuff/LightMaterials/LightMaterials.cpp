#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Utils.h"
#include "ShaderProgram.h"
#include "Camera.h"

constexpr int SCR_WIDTH = 800, SCR_HEIGHT = 600;
Camera camera;
double deltaTime, lastFrame;
glm::mat4 projection;

float vertices[]{
	-0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
};

void cursor_callback(GLFWwindow* window, double x, double y)
{
	camera.proccess_mouse(deltaTime, x, y);
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
	projection = glm::perspective(glm::radians(45.0f), (float)w / h, 0.1f, 100.0f);
}

void proccess_input(GLFWwindow* window)
{
	bool sprint = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		sprint = true;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::FORWARD, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::BACKWARD, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::LEFT, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::RIGHT, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::UP, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::DOWN, deltaTime, sprint);
}

int main()
{
	GLFWwindow* window = initWindow(SCR_WIDTH, SCR_HEIGHT, "Light Materials", cursor_callback, resize_callback);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	ShaderProgram cubeProgram({
		{ "..\\LightMaterials\\Shaders\\cube.vs", GL_VERTEX_SHADER },
		{ "..\\LightMaterials\\Shaders\\cube.fs", GL_FRAGMENT_SHADER },
	});

	// Store data
	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	cubeProgram.Use();
	projection = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);

	while (!glfwWindowShouldClose(window)) {
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		proccess_input(window);

		glBindVertexArray(VAO);
		cubeProgram.Use();
		glm::mat4 model;

		cubeProgram.SetMat4("projection", projection);
		cubeProgram.SetMat4("view", camera.GetViewMatrix());
		cubeProgram.SetMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}