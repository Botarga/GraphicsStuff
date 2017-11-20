#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "stb_image.h"
#include "Camera.h"
#include "Utils.h"
#include "Texture.h"

constexpr int SCR_WIDTH = 800, SCR_HEIGHT = 600;
GLFWwindow* window = nullptr;

Camera camera;
double deltaTime;
double lastFrame;

const float vertices[]{
	// Positions			// Colors					// Texture coords
	-0.5f, 0.5f, -0.5f,		1.0f, 0.0f, 0.0f, 1.0f,		1.0f, 1.0f,	// back Top Left  0
	0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f, 1.0f,		0.0f, 1.0f, // back top Right
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f, 1.0f,		1.0f, 0.0f, // back cottom left
	0.5f, -0.5f, -0.5f,		0.0f, 1.0f, 1.0f, 1.0f,		0.0f, 0.0f,	// back bottom Right

	-0.5f, 0.5f, 0.5f,		1.0f, 0.0f, 0.0f, 1.0f,		0.0f, 1.0f,	// front Top Left  4
	0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f, 1.0f,		1.0f, 1.0f, // front top Right
	-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f, 1.0f,		0.0f, 0.0f, // front cottom left
	0.5f, -0.5f, 0.5f,		0.0f, 1.0f, 1.0f, 1.0f,		1.0f, 0.0f	// front bottom Right
};

unsigned int indices[]{
	0, 1, 2,
	1, 2, 3,

	4, 5, 6,
	5, 6, 7,

	0, 4, 2,
	4, 2, 6,

	5, 1, 7,
	1, 7, 3,

	2, 3, 6,
	3, 6, 7,

	0, 1, 4,
	1, 4, 5
};

std::vector<glm::vec3> cubePositions; 

glm::mat4 projection;
float fov = 45.0f;

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
	projection = glm::perspective(glm::radians(fov), (float)(w / h), 0.1f, 100.0f);
}

void cursor_callback(GLFWwindow* window, double x, double y)
{
	camera.proccess_mouse(deltaTime, x, y);
}

void proccessInput(GLFWwindow* window)
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
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		cubePositions.push_back(glm::vec3(
			rand() % 50 + (rand() % 100) / 100.0f,
			rand() % 50 + (rand() % 100) / 100.0f,
			rand() % 50 + (rand() % 100) / 100.0f
		));
	}
}

int main()
{
	srand(time(0));

	cubePositions.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
	cubePositions.push_back(glm::vec3(0.0f, 2.0f, -3.0f));
	cubePositions.push_back(glm::vec3(0.0f, 0.0f, 5.0f));

	window = initWindow(SCR_WIDTH, SCR_HEIGHT, "Basic scene", cursor_callback, resize_callback);

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);

	// Shaders
	ShaderProgram cubeProgram({ 
		{ "..\\BasicScene\\Shaders\\camera.vs", GL_VERTEX_SHADER },
		{ "..\\BasicScene\\Shaders\\camera.fs", GL_FRAGMENT_SHADER } 
	});

	// Load textures
	Texture waterTexture("..\\BasicScene\\Textures\\water.jpg", GL_TEXTURE_2D, false);
	Texture konataTexture("..\\BasicScene\\Textures\\konata.png", GL_TEXTURE_2D);

	// bind to shaders
	cubeProgram.Use();
	cubeProgram.SetInt("texture1", 0);
	cubeProgram.SetInt("texture2", 1);

	// Store data
	GLuint VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}
	glBindVertexArray(0);

	projection = glm::perspective(glm::radians(fov), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
	cubeProgram.Use();
	cubeProgram.SetMat4("projection", projection);
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		proccessInput(window);

		// Bind textures
		glActiveTexture(GL_TEXTURE0);
		konataTexture.Bind();
		glActiveTexture(GL_TEXTURE1);
		waterTexture.Bind();

		cubeProgram.Use();
		cubeProgram.SetMat4("view", camera.GetViewMatrix());
		
		// Render
		glBindVertexArray(VAO);
		int nCubes = sizeof(cubePositions) / sizeof(glm::vec3);
		for (const auto& p : cubePositions) {
			glm::mat4 model;
			model = glm::translate(model, p);
			model = glm::rotate(model, float(glfwGetTime()), glm::vec3(0.3f, 0.5f, 0.7f));
			cubeProgram.SetMat4("model", model);

			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		}

		
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}