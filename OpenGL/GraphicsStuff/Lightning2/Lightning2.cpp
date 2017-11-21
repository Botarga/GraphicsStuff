#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Utils.h"
#include "Camera.h"
#include "ShaderProgram.h"


constexpr int SCR_WIDTH = 800, SCR_HEIGHT = 600;
GLFWwindow* window = nullptr;
Camera camera;
glm::mat4 projection;
float fov = 45.0f;
double deltaTime;
double lastFrame;

glm::vec3 cubeColor(0.5f, 0.2f, 0.8f);
glm::vec3 lampColor(1.0f, 1.0f, 1.0f);
glm::vec3 lightPosition(0.0f, 2.0f, 0.0f);

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	projection = glm::perspective(glm::radians(fov), (float)(w / h), 0.1f, 100.0f);
}

void cursor_callback(GLFWwindow* window, double x, double y)
{
	camera.proccess_mouse(deltaTime, x, y);
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

	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		lampColor[0] += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		lampColor[1] += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
		lampColor[2] += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
		lampColor[0] -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
		lampColor[1] -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
		lampColor[2] -= 0.01f;

	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		lightPosition.x -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		lightPosition.z -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		lightPosition.z += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		lightPosition.x += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		lightPosition.y += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		lightPosition.y -= 0.01f;
}

int main()
{
	window = initWindow(SCR_WIDTH, SCR_HEIGHT, "Lightning 2", cursor_callback, resize_callback);

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	ShaderProgram cubeProgram({
		{ "..\\Lightning2\\Shaders\\cube.vs", GL_VERTEX_SHADER },
		{ "..\\Lightning2\\Shaders\\cube.fs", GL_FRAGMENT_SHADER },
	});
	ShaderProgram lampProgram({
		{ "..\\Lightning2\\Shaders\\lamp.vs", GL_VERTEX_SHADER },
		{ "..\\Lightning2\\Shaders\\lamp.fs", GL_FRAGMENT_SHADER },
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
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	cubeProgram.Use();
	projection = glm::perspective(glm::radians(fov), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
	cubeProgram.SetMat4("projection", projection);

	lampProgram.Use();
	lampProgram.SetMat4("projection", projection);

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
		cubeProgram.SetVec3("cubeColor", cubeColor);
		cubeProgram.SetVec3("lightColor", lampColor);
		cubeProgram.SetVec3("lightPosition", lightPosition);
		cubeProgram.SetVec3("cameraPosition", camera.cameraPos);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		lampProgram.Use();
		glm::mat4 lightModel;
		lightModel = glm::translate(lightModel, lightPosition);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f, 0.2f, 0.2f));

		lampProgram.SetMat4("projection", projection);
		lampProgram.SetMat4("view", camera.GetViewMatrix());
		lampProgram.SetMat4("model", lightModel);
		lampProgram.SetVec3("lightColor", lampColor);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}