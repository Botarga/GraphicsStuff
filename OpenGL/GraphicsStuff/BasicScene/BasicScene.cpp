#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "stb_image.h"
#include "Camera.h"
#include "Utils.h"

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

glm::vec3 cubePositions[]{
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f,  2.0f, -3.0f),
	glm::vec3(0.0f, 0.0f, 5.0f)
};

glm::mat4 projection;
float fov = 45.0f;

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
	projection = glm::perspective(glm::radians(fov), (float)(w / h), 0.1f, 100.0f);
}

void cursor_callback(GLFWwindow* window, double x, double y)
{
	//camera.process_mouse(deltaTime, x, y);
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
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "title", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return -1;

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Shaders
	ShaderProgram triangle({ 
		{ "..\\Project3\\Shaders\\camera.vs", GL_VERTEX_SHADER },
		{ "..\\Project3\\Shaders\\camera.fs", GL_FRAGMENT_SHADER } 
	});

	// Load textures
	GLuint konataTexture, waterTexture;
	stbi_set_flip_vertically_on_load(true);
	// Texture 1
	glGenTextures(1, &konataTexture);
	glBindTexture(GL_TEXTURE_2D, konataTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	int width, height, numChannels;
	unsigned char* data = stbi_load("..\\Project3\\Textures\\Konata.png", &width, &height, &numChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}

	// Texture 2
	glGenTextures(1, &waterTexture);
	glBindTexture(GL_TEXTURE_2D, waterTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	data = stbi_load("..\\Project3\\Textures\\water.jpg", &width, &height, &numChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	// bind to shaders
	triangle.Use();
	triangle.SetInt("texture1", 0);
	triangle.SetInt("texture2", 1);

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
	triangle.Use();
	triangle.SetMat4("projection", projection);
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		proccessInput(window);

		// Bind textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, konataTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, waterTexture);

		triangle.Use();
		glm::mat4 view;
		view = camera.GetViewMatrix();
		triangle.SetMat4("view", view);
		
		// Render
		glBindVertexArray(VAO);
		int nCubes = sizeof(cubePositions) / sizeof(glm::vec3);
		for (int i = 0; i < nCubes; ++i) {
			glm::mat4 model;
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, float(glfwGetTime()), glm::vec3(0.3f, 0.5f, 0.7f));
			triangle.SetMat4("model", model);

			glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		}

		
		glfwSwapBuffers(window);
	}


	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}