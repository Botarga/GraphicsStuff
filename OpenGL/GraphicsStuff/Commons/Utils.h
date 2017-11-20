#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

GLFWwindow* initWindow(int width, int height, std::string title, GLFWcursorposfun cursorFun,
	GLFWframebuffersizefun framebufferFun) {
	GLFWwindow* window = nullptr;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferFun);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursorFun);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		return nullptr;

	glViewport(0, 0, width, height);

	return window;
}