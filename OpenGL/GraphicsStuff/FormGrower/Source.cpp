#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <ShaderProgram.h>
#include <Utils.h>
#include <Camera.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 projection = glm::mat4();
GLFWwindow* window = nullptr;
Camera camera;

double	deltaTime, 
		lastFrame = glfwGetTime();

float vertices[]{
	-0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f
};

void resize_callback(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}

void cursor_callback(GLFWwindow* window, double x, double y)
{
	camera.proccess_mouse(deltaTime, x, y);
}

void process_input(GLFWwindow* window)
{
	bool sprint = false;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	sprint = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::UP, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::DOWN, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::LEFT, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::RIGHT, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::FORWARD, deltaTime, sprint);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.proccess_input(Camera::MoveType::BACKWARD, deltaTime, sprint);

}



int main()
{
	window = initWindow(800, 600, "Form grower", cursor_callback, resize_callback);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	ShaderProgram formProgram({ 
		{"..\\FormGrower\\Shaders\\form.vs", GL_VERTEX_SHADER},
		{ "..\\FormGrower\\Shaders\\form.fs", GL_FRAGMENT_SHADER } 
	});

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window)) {
		double current = glfwGetTime();
		deltaTime = current - lastFrame;
		lastFrame = current;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();
		process_input(window);

		formProgram.Use();
		glBindVertexArray(VAO);
		
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}