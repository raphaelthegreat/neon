#pragma once
#include <string>

class GLFWwindow;

class Window {
public:
	Window(int width, int height, const std::string& name);
	~Window();

	void update();
	void resize(int width, int height);
	
	int get_width() const;
	int get_height() const;

	bool should_close() const;

	void capture_mouse(bool capture);

	GLFWwindow* get_pointer();

protected:
	static void resize_callback(GLFWwindow* window, int width, int height);

protected:
	GLFWwindow* _windowPtr;

	std::string _name = "Window";

	static int _width;
	static int _height;
};