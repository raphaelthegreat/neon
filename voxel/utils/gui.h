#pragma once
#include <utils/window.h>
#include <memory>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using std::shared_ptr;

class GuiManager {
public:
	GuiManager(shared_ptr<Window> window);
	~GuiManager();

	void update();
	void render();

protected:
	shared_ptr<Window> _window;
};