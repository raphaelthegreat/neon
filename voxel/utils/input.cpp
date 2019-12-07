#include "input.h"
#include <GLFW/glfw3.h>

std::function<void(int)> InputManager::_callback;
bool InputManager::_callback_set = false;

std::function<void(double, double)> InputManager::_mouse_callback;
bool InputManager::_mouse_callback_set = false;

InputManager::InputManager(shared_ptr<Window> window) :
	_window(window)
{
	glfwSetKeyCallback(window->get_pointer(), InputManager::glfw_key_callback);
}

bool InputManager::is_key_pressed(int keycode)
{
	auto raw_window = _window->get_pointer();
	return glfwGetKey(raw_window, keycode);
}

double InputManager::mouseX()
{
	double xpos, ypos;
	glfwGetCursorPos(_window->get_pointer(), &xpos, &ypos);

	return xpos;
}

double InputManager::mouseY()
{
	double xpos, ypos;
	glfwGetCursorPos(_window->get_pointer(), &xpos, &ypos);

	return ypos;
}

void InputManager::key_callback(std::function<void(int)> func)
{
	_callback = func;
	_callback_set = true;
}

void InputManager::mouse_callback(std::function<void(double, double)> func)
{
	_mouse_callback = func;
}

void InputManager::glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (_callback_set && action == GLFW_PRESS) {
		_callback(key);
	}
}

void InputManager::glfw_mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (_mouse_callback) {
		_mouse_callback(xpos, ypos);
	}
}
