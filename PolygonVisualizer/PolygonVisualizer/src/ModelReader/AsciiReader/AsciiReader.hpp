#ifndef __ASCII_READER_HPP__
#define __ASCII_READER_HPP__

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

// ASCII�`���f�[�^�ǂݍ���
// (x, y, z)

class AsciiReader : public ModelReader
{
	// �����萔
	inline static constexpr double DEFAULT_COLOR = 1.0;

	void ReadData(std::ifstream &file_data);
	void ReadFile(const std::string& open_file_path) override;
public:
	AsciiReader() = delete;
	AsciiReader(const std::string& open_file_path);
	~AsciiReader();
};

#endif