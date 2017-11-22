#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Camera.h"
#include "Utils.h"
#include "Material.h"
#include <iostream>
#include <cstdint>

constexpr uint32_t SCR_WIDTH = 1280;
constexpr uint32_t SCR_HEIGHT = 720;

Camera camera;
double deltaTime = 0.0f;
double lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
GLFWwindow* window = nullptr;

void resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera.proccess_mouse(deltaTime, xpos, ypos);
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


	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		lightPos.x -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		lightPos.z -= 0.01f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		lightPos.z += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		lightPos.x += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		lightPos.y += 0.01f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		lightPos.y -= 0.01f;
}

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

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

int main()
{
	window = initWindow(SCR_WIDTH, SCR_HEIGHT, "Light materials", cursor_callback, resize_callback);
	
	glEnable(GL_DEPTH_TEST);

	ShaderProgram lightingShader({ 
		{"..\\LightMaterials\\Shaders\\cube.vs", GL_VERTEX_SHADER},
		{ "..\\LightMaterials\\Shaders\\cube.fs", GL_FRAGMENT_SHADER },
	});
	ShaderProgram lampShader({
		{ "..\\LightMaterials\\Shaders\\lamp.vs", GL_VERTEX_SHADER },
		{ "..\\LightMaterials\\Shaders\\lamp.fs", GL_FRAGMENT_SHADER },
	});
	
	// first, configure the cube's VAO (and VBO)
	uint32_t VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	lightingShader.Use();
	glm::vec3 lightColor(1.0f);
	glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);
	lightingShader.SetVec3("light.ambient", ambientColor);
	lightingShader.SetVec3("light.diffuse", diffuseColor);
	lightingShader.SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	
	lightingShader.SetMat4("projection", projection);

	lampShader.Use();
	lampShader.SetMat4("projection", projection);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		proccess_input(window);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		int row = 0, column = 0;
		lightPos = glm::vec3(0.0f, 0.0f, 2.0f);
		for (auto it = AllMaterials.begin(); it != AllMaterials.end(); ++it) {
			
			lightingShader.Use();
			lightPos.x += column * 1.0f;
			lightPos.y +=  
			lightingShader.SetVec3("light.position", lightPos);
			lightingShader.SetVec3("viewPos", camera.cameraPos);
			
			if (column == 5) {
				column = 0;
				row++;
			}
		}
		// material properties
		Material m = AllMaterials.at(MaterialName::CHROME);
		lightingShader.SetVec3("material.ambient", m.ambient);
		lightingShader.SetVec3("material.diffuse", m.diffuse);
		lightingShader.SetVec3("material.specular", m.specular);
		lightingShader.SetFloat("material.shininess", m.shininess);

		// view/projection transformations
		glm::mat4 view = camera.GetViewMatrix();
		lightingShader.SetMat4("view", view);

		// world transformation
		glm::mat4 model;
		lightingShader.SetMat4("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lampShader.Use();
		lampShader.SetMat4("view", view);
		model = glm::mat4();
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
		lampShader.SetMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}

