#ifndef __PCD_READER_HPP__
#define __PCD_READER_HPP__

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

// xyz�f�[�^������
class PCDReader : public ModelReader
{
	// �w�b�_���
	inline static const char COMMENT = '#';
	inline static const std::string VERSION = "VERSION ";
	inline static const std::string FIELDS = "FIELDS ";
	inline static const std::string XYZ_RGB = "x y z rgb";
	inline static const std::string SIZE = "SIZE ";
	inline static const std::string TYPE = "TYPE ";
	inline static const std::string COUNT = "COUNT ";
	inline static const std::string WIDTH = "WIDTH ";
	inline static const std::string HEIGHT = "HEIGHT ";
	inline static const std::string VIEWPOINT = "VIEWPOINT ";
	inline static const std::string POINTS = "POINTS ";
	inline static const std::string DATA = "DATA ";
	inline static const std::string ASCII = "ascii";

	// �t�H�[�}�b�g���
	double m_version;
	bool m_rgb;
	uint32_t m_byte_size;
	uint32_t m_byte_type;
	std::vector<int> m_count;
	int m_width, m_height, m_points;
	std::vector<double> m_viewpoint;
	bool m_is_ascii;

	// �w�b�_�����Q
	bool isEqual(const std::string& iteration, const std::string& source);
	std::string ReadLine(const std::string::const_iterator& itr, const std::string& file_data);

	// �t�@�C���ǂݍ���
	void ReadFile(const std::string& open_file_path) override;
	void ReadHeader(const std::string& file_data);
	// �f�[�^�֘A
	void ReadBinary(std::ifstream& file_path);
	void ReadAscii(const std::string::const_iterator& start_itr, const std::string& file_data);
	// �w�b�_�֘A
	std::string::const_iterator ReadField(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadSize(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadType(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadCount(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadViewPoint(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadData(const std::string::const_iterator& n_itr, const std::string& file_data);
	// NOTE: �ėp1���l�ǂݎ��
	template<class T>
	std::string::const_iterator ReadNum(const std::string& SEARCH, const std::string::const_iterator& n_itr, const std::string& file_data, T* data)
	{
		std::string read_str;
		for (auto itr = n_itr; itr != file_data.end(); ++itr)
		{
			if (read_str == SEARCH)
			{
				*data = static_cast<T>(std::stod(ReadLine(itr, file_data)));
				return ++itr;
			}
			read_str.push_back(*itr);
			if (!isEqual(read_str, SEARCH))
			{
				read_str.clear();
				read_str.shrink_to_fit();
			}
		}
		return file_data.end();
	}

	// NOTE: �������̂���, ��v�ȃo�C�g�ϊ��͂��炩���ߍ쐬
	template<class T>
	inline T Byte4ToType(const char *buffer)
	{
		return static_cast<T>((buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3]);
	}
public:
	PCDReader() = delete;
	PCDReader(const std::string &open_file_path);
	~PCDReader();
};

#endif