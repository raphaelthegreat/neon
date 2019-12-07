#pragma once
#include <glm/glm.hpp>

class InputManager;
class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
	~Camera() = default;
	
	const glm::mat4 view_matrix();
	const glm::mat4 proj_matrix();

	const glm::vec3& get_position();

	void update(InputManager& manager, double deltaTime);

private:
	void update_camera();

protected:
	glm::vec3 _position, _front, _up, _right, _world_up;
	float _speed, _sensitivity, _zoom;
	float _yaw, _pitch;

	double _last_x, _last_y;
	bool _first_mouse = true;

	glm::mat4 _view, _projection;
};