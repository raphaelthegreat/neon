#include "application.h"	
#include <world/block_database.h>
#include <glad/glad.h>

void Application::init()
{
	_window = std::make_shared<Window>(800, 600, "Window");
	_input = std::make_unique<InputManager>(_window);
	_time = std::make_unique<TimeManager>();
	
	_renderer = std::make_unique<Renderer>(_window);
	_camera = std::make_unique<Camera>(glm::vec3(0.0f, 10.0f, 0.0f));

	vector<string> textures = { "texture/block.jpg", "texture/top.jpg", "texture/bottom.jpg" };
	string texture = "texture/block.jpg";

	_material = std::make_shared<Material>(textures,
		        "shaders/vertex.glsl", "shaders/fragment.glsl");
	
	_manager = std::make_unique<ChunkManager>();
	_gui = std::make_unique<GuiManager>(_window);

	_input->key_callback([&](int key) 
	{
		if (key == Key_C)
			_captured = !_captured;
	});

	auto& database = BlockData::get();
	database.set_face_tex(Block_Grass, Top, 1);
	database.set_face_tex(Block_Grass, Bottom, 2);
	database.set_face_tex(Block_Grass, Front, 0);
}

void Application::update()
{
	if (_captured) {
		_camera->update(*_input, _time->get_delta_time());
	}

	_manager->update(_camera->get_position());
	_window->capture_mouse(_captured);
}

void Application::pre_render()
{

}

void Application::render()
{
	clear_display(0.2f, 0.3f, 0.3f, 1.0f);
	
	_renderer->begin_drawing(*_camera);
	_renderer->set_material(_material);

	_manager->render(_renderer.get());
	_gui->render();
	
	_window->update();
}

bool Application::should_close() const
{
	return _window->should_close();
}
