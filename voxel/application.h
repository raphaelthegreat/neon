#pragma once
#include <iostream>
#include <utils/window.h>
#include <glm/gtc/matrix_transform.hpp>
#include <rendering/mesh.h>
#include <utils/input.h>
#include <utils/gui.h>
#include <utils/time.h>
#include <world/chunk_manager.h>
#include <rendering/material.h>
#include <world/camera.h>
#include <rendering/renderer.h>
#include <rendering/gl_helper.h>

using std::unique_ptr;

class Window;
class Application {
public:
	~Application() = default;

	void init();
	void update();

	void pre_render();
	void render();

	bool should_close() const;

protected:
	shared_ptr<Window> _window;
	
	unique_ptr<InputManager> _input;
	unique_ptr<TimeManager> _time;
	
	unique_ptr<Renderer> _renderer;
	unique_ptr<Camera> _camera;
	unique_ptr<GuiManager> _gui;

	shared_ptr<Material> _material;
	unique_ptr<ChunkManager> _manager;

	bool _captured = true;
};