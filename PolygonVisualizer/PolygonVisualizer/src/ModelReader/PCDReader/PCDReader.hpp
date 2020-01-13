#ifndef __PCD_READER_HPP__
#define __PCD_READER_HPP__

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

#define DEBUG_PCD true

// xyzデータ・4バイトを仮定
class PCDReader : public ModelReader
{
	// ヘッダ情報
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
	// デフォルト定数
	inline static constexpr double DEFAULT_COLOR = 1.0;

	// フォーマット情報
	double m_version;
	bool m_rgb;
	uint32_t m_byte_size;
	uint32_t m_byte_type;
	std::vector<int> m_count;
	int m_width, m_height, m_points;
	std::vector<double> m_viewpoint;
	bool m_is_ascii;

	// ヘッダ処理群
	bool isEqual(const std::string& iteration, const std::string& source);
	std::string ReadLine(const std::string::const_iterator& itr, const std::string& file_data);

	// ファイル読み込み
	void ReadFile(const std::string& open_file_path) override;
	void ReadHeader(const std::string& file_data);
	// データ関連
	void ReadBinary(std::ifstream& file_path);
	void ReadAscii(std::ifstream &file_path);
	void SetDataNoRGB(const std::vector<float> &point_data);
	// ヘッダ関連
	std::string::const_iterator ReadField(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadSize(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadType(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadCount(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadViewPoint(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadData(const std::string::const_iterator& n_itr, const std::string& file_data);
	// NOTE: 汎用1数値読み取り
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

	// NOTE: リトルエンディアン -> ビッグエンディアン
	inline float IEEE754_32(const char *buffer)
	{
		uint32_t data = 0;
		data |= (static_cast<unsigned char>(buffer[3]) << 24);
		data |= (static_cast<unsigned char>(buffer[2]) << 16);
		data |= (static_cast<unsigned char>(buffer[1]) <<  8);
		data |= (static_cast<unsigned char>(buffer[0]) <<  0);
		// 32bit仮定に注意
		return reinterpret_cast<float&>(data);
	}
public:
	PCDReader() = delete;
	PCDReader(const std::string &open_file_path);
	~PCDReader();
};

#endif