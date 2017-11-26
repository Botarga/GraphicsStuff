#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <ctime>

constexpr int WIDTH = 1280, HEIGHT = 720;
GLFWwindow* window = nullptr;

glm::vec3 cameraPos(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

double deltaTime, lastFrame = glfwGetTime();
bool firstMouse = true;
double lastX = WIDTH / 2.0, lastY = HEIGHT / 2.0;
double yaw = -90.0, pitch = 0.0;

float vertices[2000];

float colors[2000];

int numVertexDraw = 3;
GLuint VAO, VBO, colorVBO;

void proccess_input(GLFWwindow* window) {
	float cameraSpeed = 8.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed += cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		vertices[numVertexDraw * 3] = (float)(rand() % 21 -10 + (rand() % 101 * 0.01f));
		vertices[numVertexDraw * 3 + 1] = (float)(rand() % 21 - 10 + (rand() % 101 * 0.01f));
		vertices[numVertexDraw * 3 + 2] = (float)(rand() % 21 -10 + (rand() % 101 * 0.01f));

		colors[numVertexDraw * 3] = (float)(rand() % 101 * 0.01f);
		colors[numVertexDraw * 3 + 1] = (float)(rand() % 101 * 0.01f);
		colors[numVertexDraw * 3 + 2] = (float)(rand() % 101 * 0.01f);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(colors), colors);

		numVertexDraw++;
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && numVertexDraw > 3)
		numVertexDraw--;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraFront * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraFront * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		cameraPos += cameraUp * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		cameraPos -= cameraUp * cameraSpeed;
}

void cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	double sensitivity = 0.1;

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	double offsetX = xpos - lastX;
	double offsetY = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	offsetX *= sensitivity;
	offsetY *= sensitivity;

	yaw += offsetX;
	pitch += offsetY;
	if (pitch >= 89.0)
		pitch = 89.0;
	else if (pitch <= -89.0)
		pitch = -89.0;

	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
}

GLuint loadShaders(const char* vertexPath, const char* fragmentPath)
{
	GLuint program = glCreateProgram();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint auxInt;

	std::ifstream vertexFile(vertexPath);
	std::string vertexContent((std::istreambuf_iterator<char>(vertexFile)), (std::istreambuf_iterator<char>()));
	vertexFile.close();
	std::ifstream fragmentFile(fragmentPath);
	std::string fragmentContent((std::istreambuf_iterator<char>(fragmentFile)), (std::istreambuf_iterator<char>()));
	fragmentFile.close();
	const char* vertexCode = vertexContent.c_str();
	const char* fragmentCode = fragmentContent.c_str();

	glShaderSource(vertexShader, 1, &vertexCode, 0);
	glShaderSource(fragmentShader, 1, &fragmentCode, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	
	bool compileError = false;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &auxInt);
	if (!auxInt) {
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &auxInt);
		char* message = new char[auxInt];
		glGetShaderInfoLog(vertexShader, auxInt, 0, message);
		std::cerr << "VERTEX_SHADER_ERROR::" << message << std::endl;
		delete[] message;
		compileError = true;
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &auxInt);
	if (!auxInt) {
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &auxInt);
		char* message = new char[auxInt];
		glGetShaderInfoLog(fragmentShader, auxInt, 0, message);
		std::cerr << "FRAGMENT_SHADER_ERROR::" << message << std::endl;
		delete[] message;
		compileError = true;
	}
	
	if (!compileError) {
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &auxInt);
		if (!auxInt) {
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &auxInt);
			char* message = new char[auxInt];
			glGetProgramInfoLog(program, auxInt, 0, message);
			std::cerr << "PROGAM_LINK_ERROR::" << message << std::endl;
			delete[] message;
		}
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	return program;
}


int main()
{
	srand(time(0));
	vertices[0] = -0.5f;
	vertices[1] = -0.5f;
	vertices[2] =  0.0f;

	vertices[3] =  0.0f;
	vertices[4] =  0.5f;
	vertices[5] =  0.0f;

	vertices[6] =  0.5f;
	vertices[7] = -0.5f;
	vertices[8] =  0.0f;

	//vertices[9] = 2.0f;
	//vertices[10] = 2.0f;
	//vertices[11] = -1.0f;

	colors[0] = 1.0f;
	colors[1] = 0.0f;
	colors[2] = 0.0f;
	colors[3] = 1.0f;
	colors[4] = 0.0f;
	colors[5] = 0.0f;
	colors[6] = 1.0f;
	colors[7] = 0.0f;
	colors[8] = 0.0f;
	//colors[9] = 1.0f;
	//colors[10] = 0.0f;
	//colors[11] = 0.0f;


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WIDTH, HEIGHT, "", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_callback);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return -1;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	// Shaders
	GLuint programId = loadShaders("..\\FormGrower\\Shaders\\shader.vs", "..\\FormGrower\\Shaders\\shader.fs");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &colorVBO);

	glBindVertexArray(VAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		glfwPollEvents();
		proccess_input(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(programId);
		glm::mat4 model = glm::mat4();
		glm::mat4 projection;
		glm::mat4 view;

		projection = glm::perspective(glm::radians(45.0f), (float)(WIDTH / HEIGHT), 0.1f, 100.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glUniformMatrix4fv(glGetUniformLocation(programId, "model"), 1, GL_FALSE, &model[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programId, "projection"), 1, GL_FALSE, &projection[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(programId, "view"), 1, GL_FALSE, &view[0][0]);
		
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, numVertexDraw);
		glfwSwapBuffers(window);
	}
	
	glDeleteProgram(programId);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}