#include "color.h"

#define GL_VERSION_4_6
#include <glad/glad.h>

Color::Color(float r, float g, float b, float a)
{
	_r = r;
	_b = b;
	_g = g;
	_a = a;
}

void Color::set_color(float r, float g, float b)
{
	_r = r;
	_b = b;
	_g = g;
}

void Color::set_alpha(float a)
{
	_a = a;
}

void clear_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void clear_display(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void clear_display(Color color)
{
	glClearColor(color.red(), color.green(), color.blue(), color.alpha());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}
