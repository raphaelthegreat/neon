#include "camera.h"
#include <utils/input.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up)
{
	_position = position;
	_world_up = up;
	_yaw = -90.0f;
	_pitch = 0.0f;

	_front = glm::vec3(0.0f, 0.0f, -1.0f); 
	_speed = 58.5f; 
	_sensitivity = 0.1f;
	_zoom = 45.0f;

	_projection = glm::mat4(1.0f);
	_projection = glm::perspective(glm::radians(_zoom), 4.0f / 3.0f, 0.1f, 1000.0f);

	update_camera();
}

const glm::mat4 Camera::view_matrix()
{
	return _view;
}

const glm::mat4 Camera::proj_matrix()
{
	return _projection;
}

const glm::vec3& Camera::get_position()
{
	return _position;
}

void Camera::update(InputManager& manager, double deltaTime)
{
	float velocity = _speed * (float)deltaTime;
	if (manager.is_key_pressed(Key_W))
		_position += _front * velocity;
	if (manager.is_key_pressed(Key_S))
		_position -= _front * velocity;
	if (manager.is_key_pressed(Key_A))
		_position -= _right * velocity;
	if (manager.is_key_pressed(Key_D))
		_position += _right * velocity;

	if (_first_mouse)
	{
		_last_x = manager.mouseX();
		_last_y = manager.mouseY();
		_first_mouse = false;
	}

	double xpos = manager.mouseX(), ypos = manager.mouseY();

	double xoffset = xpos - _last_x;
	double yoffset = _last_y - ypos;

	_last_x = xpos;
	_last_y = ypos;
	
	xoffset *= static_cast<double>(_sensitivity);
	yoffset *= static_cast<double>(_sensitivity);

	_yaw += static_cast<float>(xoffset);
	_pitch += static_cast<float>(yoffset);

	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	this->update_camera();
}

void Camera::update_camera()
{
	glm::vec3 front = glm::vec3(0.0f);
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front = glm::normalize(front);

	_right = glm::normalize(glm::cross(_front, _world_up));
	_up = glm::normalize(glm::cross(_right, _front));

	_view = glm::lookAt(_position, _position + _front, _up);
}
