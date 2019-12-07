#include <glm/gtc/matrix_transform.hpp>
#include "renderer.h"
#include "gl/draw.h"
#include <iostream>

Renderer::Renderer(shared_ptr<Window> window)
{
	_model = glm::mat4(1.0f);
	_window = window;
}

void Renderer::begin_drawing(Camera& cam)
{
	float x = static_cast<float>(_window->get_width());
	float y = static_cast<float>(_window->get_height());

	_view = cam.view_matrix();
	_projection = glm::perspective(glm::radians(60.0f), x / y, 0.1f, 1000.0f);
}

void Renderer::set_material(shared_ptr<Material> mat)
{
	_material = mat;
	_material->bind();

	_material->get_shader().set_mat4("view", _view);
	_material->get_shader().set_mat4("proj", _projection);
}

void Renderer::set_translation(const glm::vec3& pos)
{
	_model = glm::translate(glm::mat4(1.0f), pos);
	_material->bind();
	_material->get_shader().set_mat4("model", _model);
}

void Renderer::draw(shared_ptr<Mesh> mesh)
{
	mesh->bind();
	gl::draw_indexed(mesh->get_index_count());
}
