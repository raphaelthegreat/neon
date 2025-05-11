#include "draw.h"
#include "buffer.h"
#include "shader.h"
#include <iostream>

#define GL_VERSION_4_6
#include <glad/glad.h>

void gl::draw_buffer(int vert_count)
{
	glDrawArrays(GL_TRIANGLES, 0, vert_count);
}

void gl::draw_indexed(int vert_count)
{
	glDrawElements(GL_TRIANGLES, vert_count, GL_UNSIGNED_INT, 0);
}
