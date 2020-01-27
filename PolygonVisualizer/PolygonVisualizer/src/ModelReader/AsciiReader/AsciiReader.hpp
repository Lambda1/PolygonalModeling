#ifndef __ASCII_READER_HPP__
#define __ASCII_READER_HPP__

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

// ASCII形式データ読み込み
// (x, y, z) or (x, y, z, r, g, b)

class AsciiReader : public ModelReader
{
	// 初期定数
	inline static constexpr double DEFAULT_COLOR = 1.0;
	inline static constexpr int RGB_VERTEX_COUNT = 5;
	inline static constexpr int BIN_VERTEX_COUNT = 2;

	void ReadData(std::ifstream &file_data);
	void ReadFile(const std::string& open_file_path) override;

	void SendVertexColor(const std::vector<float> &data);
	void SendVertex(const std::vector<float> &data);
public:
	AsciiReader() = delete;
	AsciiReader(const std::string& open_file_path);
	~AsciiReader();
};

#endif