#ifndef __BIN4_READER_HPP__
#define __BIN4_READER_HPP__

/*
	.bin4ファイル読み込み(独自形式)
	1行目: 列ベクトル数(通常7ベクトル: x,y,z,r,g,b,alpha)
	2行目以降: 4バイト毎にベクトル

	NOTE: 現段階では3, 7ベクトル読み込みにのみ対応
*/

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

class Bin4Reader : public ModelReader
{
	// 定数パラメータ
	inline static constexpr int BASE_VECTOR = 7;   // 点群+色ベクトル数
	inline static constexpr int POINTS_VECTOR = 3; // 基本ベクトル数
	// floatを4バイト仮定
	using BYTE_4 = float;

	// ベクトル数
	int m_vec_num;

	void ReadFile(const std::string& open_file_path) override;
	void ReadHeader(std::ifstream &file_stream);
	void ReadDataNormalFormat(std::ifstream &file_stream);
	void ReadDataOnlyPoint(std::ifstream& file_stream);

public:
	Bin4Reader() = delete;
	Bin4Reader(const std::string& open_file_path);
	~Bin4Reader();
};

#endif