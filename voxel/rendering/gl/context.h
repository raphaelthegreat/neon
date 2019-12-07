#pragma once

#include <string>

using std::string;

namespace gl {

const string gl_version();
const string gl_vendor();
const string gl_renderer();
int gl_extensions();

}