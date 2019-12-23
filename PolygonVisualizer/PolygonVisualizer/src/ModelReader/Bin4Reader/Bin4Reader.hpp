#ifndef __BIN4_READER_HPP__
#define __BIN4_READER_HPP__

/*
	.bin4�t�@�C���ǂݍ���(�Ǝ��`��)
	1�s��: ��x�N�g����(�ʏ�7�x�N�g��: x,y,z,r,g,b,alpha)
	2�s�ڈȍ~: 4�o�C�g���Ƀx�N�g��

	NOTE: ���i�K�ł�3, 7�x�N�g���ǂݍ��݂ɂ̂ݑΉ�
*/

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

class Bin4Reader : public ModelReader
{
	// �萔�p�����[�^
	inline static constexpr int BASE_VECTOR = 7;   // �_�Q+�F�x�N�g����
	inline static constexpr int POINTS_VECTOR = 3; // ��{�x�N�g����
	// float��4�o�C�g����
	using BYTE_4 = float;

	// �x�N�g����
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