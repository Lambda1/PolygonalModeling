#ifndef __PCD_READER_HPP__
#define __PCD_READER_HPP__

#include "../ModelReader.hpp"

#include <fstream>
#include <string>

class PCDReader : public ModelReader
{
	void ReadFile(const std::string &open_file_path);
public:
	PCDReader() = delete;
	PCDReader(const std::string &open_file_path);
	~PCDReader();
};

#endif