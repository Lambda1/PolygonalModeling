#include "./PCDReader.hpp"

PCDReader::PCDReader(const std::string& open_file_path):
	m_version(0.0), m_rgb(false), m_byte_size(0)
{
	ReadFile(open_file_path);
}

PCDReader::~PCDReader()
{
}

// private
// ヘッダ処理
bool PCDReader::isEqual(const std::string& iteration, const std::string& source)
{
	for (int i = 0; i < iteration.length(); ++i)
	{
		if (iteration[i] != source[i])
		{
			return false;
		}
	}
	return true;
}
// NOTE: ヘッダ終端記号の\nまで読み込む
std::string PCDReader::ReadLine(const std::string::const_iterator& itr, const std::string& file_data)
{
	std::string read_str;
	for (auto n_itr = itr; n_itr != file_data.end(); ++n_itr)
	{
		if (*n_itr == '\n') break;
		read_str.push_back(*n_itr);
	}
	return read_str;
}

// ファイル読み込み
void PCDReader::ReadFile(const std::string& open_file_path)
{
	std::ifstream file_stream(open_file_path, std::ios::in | std::ios::binary);
	if (file_stream.fail())
	{
		std::cerr << "ERROR: CANNOT READ PCD FILE." << std::endl;
		std::cerr << __FILE__ << " " << __LINE__ << std::endl;
		std::abort();
	}

	// 1バイト単位で一括読み込み
	std::string file_data((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
	file_stream.close();

	// ヘッダ読み込み
	ReadHeader(file_data);
}
// NOTE: ファイルフォーマットに従って処理
void PCDReader::ReadHeader(const std::string& file_data)
{
	std::string::const_iterator next_itr = file_data.begin();

	next_itr = ReadVersion(next_itr, file_data);
	next_itr = ReadField(next_itr, file_data);
	next_itr = ReadSize(next_itr, file_data);

	std::cout << "VERSION " << m_version << std::endl;
	std::cout << "RGB " << m_rgb << std::endl;
	std::cout << "SIZE " << m_byte_size << std::endl;
}
// 各種読み込み部
// NOTE: 続きのイテレータを返す
std::string::const_iterator PCDReader::ReadVersion(const std::string::const_iterator& n_itr, const std::string& file_data)
{
	std::string read_str;
	for (auto itr = n_itr; itr != file_data.end(); ++itr)
	{
		if (read_str == VERSITON)
		{
			m_version = std::stod(ReadLine(itr, file_data));
			return ++itr;
		}
		read_str.push_back(*itr);
		if (!isEqual(read_str, VERSITON))
		{
			read_str.clear();
			read_str.shrink_to_fit();
		}
	}
	return file_data.end();
}
std::string::const_iterator PCDReader::ReadField(const std::string::const_iterator& n_itr, const std::string& file_data)
{
	std::string read_str;
	for (auto itr = n_itr; itr != file_data.end(); ++itr)
	{
		if (read_str == FIELDS)
		{
			if (ReadLine(itr, file_data) == XYZ_RGB) { m_rgb = true; }
			else { m_rgb = false; }
			return ++itr;
		}
		read_str.push_back(*itr);
		if (!isEqual(read_str, FIELDS))
		{
			read_str.clear();
			read_str.shrink_to_fit();
		}
	}
	return file_data.end();
}
std::string::const_iterator PCDReader::ReadSize(const std::string::const_iterator& n_itr, const std::string& file_data)
{
	std::string read_str;
	int shifter = 0;
	for (auto itr = n_itr; itr != file_data.end(); ++itr)
	{
		if (read_str == SIZE)
		{
			std::string byte_str = ReadLine(itr, file_data);
			for (auto m_itr = byte_str.begin(); m_itr != byte_str.end(); ++m_itr)
			{
				if (*m_itr != ' ')
				{
					m_byte_size |= static_cast<uint32_t>(*m_itr - '0') << shifter;
					shifter += 4;
				}
			}
			return ++itr;
		}
		read_str.push_back(*itr);
		if (!isEqual(read_str, SIZE))
		{
			read_str.clear();
			read_str.shrink_to_fit();
		}
	}
	return file_data.end();
}