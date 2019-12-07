#pragma once
#include <utils/window.h>
#include <utils/key_code.h>
#include <functional>
#include <memory>

using std::shared_ptr;

class InputManager {
public:
	InputManager(shared_ptr<Window> window);
	~InputManager() = default;

	bool is_key_pressed(int keycode);

	double mouseX();
	double mouseY();

	void key_callback(std::function<void(int)> func);
	void mouse_callback(std::function<void(double, double)> func);

protected:
	static void glfw_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void glfw_mouse_callback(GLFWwindow* window, double xpos, double ypos);

protected:
	shared_ptr<Window> _window;

	static std::function<void(int)> _callback;
	static std::function<void(double, double)> _mouse_callback;
	
	static bool _callback_set;
	static bool _mouse_callback_set;
};