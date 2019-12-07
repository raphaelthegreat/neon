#include "fileio.h"
#include <sstream>

File::File(const string name, OpenMode mode)
{
	if (mode == Read) {
		_infile.open(name);
	}
	else {
		_outfile.open(name);
	}

	_mode = mode;
	_opened = true;
}

File::~File()
{
	if (_mode = Read) {
		_infile.close();
	}
	else {
		_outfile.close();
	}
}

void File::open(const string name, OpenMode mode)
{
	if (mode == Read) {
		_infile.open(name);
	}
	else {
		_outfile.open(name);
	}

	_mode = mode;
	_opened = true;
}

void File::close()
{
	if (_mode = Read) {
		_infile.close();
	}
	else {
		_outfile.close();
	}
}

const string File::read()
{
	if (_mode == Read) {
		std::stringstream stream;
		stream << _infile.rdbuf();

		string str = stream.str();
		return str;
	}
}

void File::write(const string text)
{
	if (_mode == Write) {
		_outfile << text;
	}
}
