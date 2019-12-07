#pragma once
#include <world/camera.h>
#include <rendering/material.h>
#include <rendering/mesh.h>
#include <utils/window.h>
#include <unordered_map>
#include <memory>

using std::shared_ptr;
using std::unordered_map;

class Renderer {
public:
	Renderer() = default;
	Renderer(shared_ptr<Window> window);
	~Renderer() = default;

	void begin_drawing(Camera& cam);

	void set_material(shared_ptr<Material> mat);
	void pop_material();

	void set_translation(const glm::vec3& pos);

	void draw(shared_ptr<Mesh> mesh);

protected:
	glm::mat4 _view, _projection, _model;
	
	shared_ptr<Material> _material;
	shared_ptr<Mesh> _mesh;

	shared_ptr<Window> _window;
};