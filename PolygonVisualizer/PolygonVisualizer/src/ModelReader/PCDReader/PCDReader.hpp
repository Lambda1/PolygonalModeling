#ifndef __PCD_READER_HPP__
#define __PCD_READER_HPP__

#include "../ModelReader.hpp"

#include <iostream>
#include <fstream>
#include <string>

// xyzデータを仮定
class PCDReader : public ModelReader
{
	// ヘッダ情報
	inline static const char COMMENT = '#';
	inline static const std::string VERSITON = "VERSION ";
	inline static const std::string FIELDS = "FIELDS ";
	inline static const std::string XYZ_RGB = "x y z rgb";
	inline static const std::string SIZE = "SIZE ";
	inline static const std::string TYPE = "TYPE ";

	// フォーマット情報
	double m_version;
	bool m_rgb;
	uint32_t m_byte_size;
	uint32_t m_byte_type;

	// ヘッダ処理群
	bool isEqual(const std::string &iteration, const std::string &source);
	std::string ReadLine(const std::string::const_iterator &itr,const std::string &file_data);

	// ファイル読み込み
	void ReadFile(const std::string &open_file_path) override;
	void ReadHeader(const std::string &file_data);
	std::string::const_iterator ReadVersion(const std::string::const_iterator &n_itr, const std::string &file_data);
	std::string::const_iterator ReadField(const std::string::const_iterator& n_itr, const std::string& file_data);
	std::string::const_iterator ReadSize(const std::string::const_iterator& n_itr, const std::string& file_data);
public:
	PCDReader() = delete;
	PCDReader(const std::string &open_file_path);
	~PCDReader();
};

#endif