#include "window.h"
#include <rendering/gl/context.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

int Window::_height = 800;
int Window::_width = 600;

Window::Window(int width, int height, const std::string& name)
{
	glfwInit();

	_windowPtr = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	
	glfwMakeContextCurrent(_windowPtr);
	glfwSetInputMode(_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1);

	GLFWimage images[1]; 
	images[0].pixels = stbi_load("texture/icon.png", &images[0].width, &images[0].height, 0, STBI_rgb_alpha);

	glfwSetWindowIcon(_windowPtr, 1, images);
	stbi_image_free(images[0].pixels);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "[ERROR] Unable to load OpenGL function pointers!\n";
	}
	else {
		std::cout << "[INFO] OpenGL Version: " << gl::gl_version() << "\n";
		std::cout << "[INFO] OpenGL Vendor: " << gl::gl_vendor() << "\n";
		std::cout << "[INFO] OpenGL Renderer: " << gl::gl_renderer() << std::endl;
	}

	glfwSetFramebufferSizeCallback(_windowPtr, Window::resize_callback);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_width = width;
	_height = height;
	_name = name;
}

Window::~Window()
{
	glfwDestroyWindow(_windowPtr);
}

void Window::update()
{
	glfwPollEvents();
	glfwSwapBuffers(_windowPtr);
}

void Window::resize(int width, int height)
{
	glfwSetWindowSize(_windowPtr, width, height);
	_width = width;
	_height = height;
}

int Window::get_width() const
{
	return _width;
}

int Window::get_height() const
{
	return _height;
}

bool Window::should_close() const
{
	return glfwWindowShouldClose(_windowPtr);
}

void Window::capture_mouse(bool capture)
{
	if (capture)
		glfwSetInputMode(_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	else
		glfwSetInputMode(_windowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

GLFWwindow* Window::get_pointer()
{
	return _windowPtr;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	_width = width;
	_height = height;
}
