#ifndef __ASCII_READER_HPP__
#define __ASCII_READER_HPP__

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

// ASCII形式データ読み込み
// (x, y, z)

class AsciiReader : public ModelReader
{
	void ReadData(std::ifstream &file_data);
	void ReadFile(const std::string& open_file_path) override;
public:
	AsciiReader() = delete;
	AsciiReader(const std::string& open_file_path);
	~AsciiReader();
};

#endif