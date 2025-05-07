#include "context.h"

#define GL_VERSION_4_6
#include <glad/glad.h>

const string gl::gl_version()
{
	const GLubyte* version = glGetString(GL_VERSION);
	const char* c_version = reinterpret_cast<const char*>(version);

	return c_version;
}

const string gl::gl_vendor()
{
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const char* c_vendor = reinterpret_cast<const char*>(vendor);

	return c_vendor;
}

const string gl::gl_renderer()
{
	const GLubyte* renderer = glGetString(GL_RENDERER);
	const char* c_renderer = reinterpret_cast<const char*>(renderer);

	return c_renderer;
}

int gl::gl_extensions()
{
	int extensions = 0;
	glGetIntegerv(GL_EXTENSIONS, &extensions);

	return extensions;
}
