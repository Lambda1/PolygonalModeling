#ifndef __ASCII_READER_HPP__
#define __ASCII_READER_HPP__

#include "../ModelReader.hpp"

#include <string>

class AsciiReader : public ModelReader
{
	void ReadFile(const std::string& open_file_path) override;
public:
	AsciiReader() = delete;
	AsciiReader(const std::string& open_file_path);
	~AsciiReader();
};

#endif