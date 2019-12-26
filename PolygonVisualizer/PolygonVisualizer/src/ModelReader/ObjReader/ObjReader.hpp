#ifndef __OBJ_READER_HPP__
#define __OBJ_READER_HPP__

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

class ObjReader : public ModelReader
{
public:
	inline static const char OBJ_FORMAT_COMMENT = '#';
	inline static const char OBJ_FORMAT_DELIMITER = ' ';
private:

	void ReadFile(const std::string& open_file_path);
	std::vector<Vector> ReadVertex(std::ifstream &file_data);
	Vector ReadLineData(std::string &buffer);
public:
	ObjReader() = delete;
	ObjReader(const std::string& open_file_path);
	~ObjReader();
};

#endif