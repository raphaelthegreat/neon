#pragma once
#include <fstream>
#include <string>
#include <iostream>

using std::string;

enum OpenMode {
	Read,
	Write
};

class File {
public:
	File() = default;
	File(const string name, OpenMode mode = OpenMode::Read);
	~File();

	void open(const string name, OpenMode mode = OpenMode::Read);
	void close();

	const string read();
	void write(const string text);

protected:
	bool _opened = false;
	
	std::ifstream _infile;
	std::ofstream _outfile;

	OpenMode _mode;
};