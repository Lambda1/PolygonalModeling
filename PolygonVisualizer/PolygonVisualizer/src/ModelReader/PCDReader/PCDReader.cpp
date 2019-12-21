#include "./PCDReader.hpp"

PCDReader::PCDReader(const std::string& open_file_path):
	m_version(0.0), m_rgb(false), m_byte_size(0), m_byte_type(0),
	m_width(0), m_height(0), m_points(0)
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
// ファイルフォーマット読み込み
// NOTE: 冗長な処理となるがフォーマットは全て保存する.
void PCDReader::ReadHeader(const std::string& file_data)
{
	std::string::const_iterator next_itr = file_data.begin();

	next_itr = ReadNum<double>(VERSION, next_itr, file_data, &m_version);
	next_itr = ReadField(next_itr, file_data);
	next_itr = ReadSize(next_itr, file_data);
	next_itr = ReadType(next_itr, file_data);
	next_itr = ReadCount(next_itr, file_data);
	next_itr = ReadNum<int>(WIDTH, next_itr, file_data, &m_width);
	next_itr = ReadNum<int>(HEIGHT, next_itr, file_data, &m_height);
	next_itr = ReadViewPoint(next_itr, file_data);
	next_itr = ReadNum<int>(POINTS, next_itr, file_data, &m_points);
	next_itr = ReadData(next_itr, file_data);

	std::cout << "VERSION " << m_version << std::endl;
	std::cout << "RGB " << m_rgb << std::endl;
	std::cout << "SIZE " << m_byte_size << std::endl;
	std::cout << "TYPE " << m_byte_type << std::endl;
	std::cout << "W H " << m_width << " " << m_height << std::endl;
	std::cout << "COUNT "; for (auto itr = m_count.begin(); itr != m_count.end(); ++itr) std::cout << *itr << " "; std::cout << std::endl;
	std::cout << "VIEWP "; for (auto itr = m_viewpoint.begin(); itr != m_viewpoint.end(); ++itr) std::cout << *itr << " ";
	std::cout << std::endl;
	std::cout << "POINTS " << m_points << std::endl;
	std::cout << "ASCII " << m_is_ascii << std::endl;
}
// 各種読み込み部
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
// NOTE: 4bitフィールド
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
// NOTE: 4bitフィールド
std::string::const_iterator PCDReader::ReadType(const std::string::const_iterator& n_itr, const std::string& file_data)
{
	std::string read_str;
	int shifter = 0;
	for (auto itr = n_itr; itr != file_data.end(); ++itr)
	{
		if (read_str == TYPE)
		{
			std::string byte_str = ReadLine(itr, file_data);
			for (auto m_itr = byte_str.begin(); m_itr != byte_str.end(); ++m_itr)
			{
				if (*m_itr != ' ')
				{
					// A～Fのため, バイアスとして10を加える
					m_byte_type |= static_cast<uint32_t>(*m_itr - 'A' + 10) << shifter;
					shifter += 4;
				}
			}
			return ++itr;
		}
		read_str.push_back(*itr);
		if (!isEqual(read_str, TYPE))
		{
			read_str.clear();
			read_str.shrink_to_fit();
		}
	}
	return file_data.end();
}
// NOTE: VFHの読み込みも想定してvector管理
std::string::const_iterator PCDReader::ReadCount(const std::string::const_iterator& n_itr, const std::string& file_data)
{
	std::string read_str;
	for (auto itr = n_itr; itr != file_data.end(); ++itr)
	{
		if (read_str == COUNT)
		{
			std::string byte_str = ReadLine(itr, file_data);
			for (auto m_itr = byte_str.begin(); m_itr != byte_str.end(); ++m_itr)
			{
				if (*m_itr != ' ') { m_count.push_back(std::stoi(std::string{ *m_itr })); }
			}
			return ++itr;
		}
		read_str.push_back(*itr);
		if (!isEqual(read_str, COUNT))
		{
			read_str.clear();
			read_str.shrink_to_fit();
		}
	}
	return file_data.end();
}
std::string::const_iterator PCDReader::ReadViewPoint(const std::string::const_iterator& n_itr, const std::string& file_data)
{
	std::string read_str;
	for (auto itr = n_itr; itr != file_data.end(); ++itr)
	{
		if (read_str == VIEWPOINT)
		{
			std::string byte_str = ReadLine(itr, file_data);
			std::string str_itr;
			for (auto m_itr = byte_str.begin(); m_itr != byte_str.end(); ++m_itr)
			{
				str_itr.push_back(*m_itr);
				if (*m_itr == ' ') 
				{
					m_viewpoint.push_back(std::stoi(str_itr));
					str_itr.clear();
					str_itr.shrink_to_fit();
				}
			}
			m_viewpoint.push_back(std::stoi(str_itr));
			return ++itr;
		}
		read_str.push_back(*itr);
		if (!isEqual(read_str, VIEWPOINT))
		{
			read_str.clear();
			read_str.shrink_to_fit();
		}
	}
	return file_data.end();
}
std::string::const_iterator PCDReader::ReadData(const std::string::const_iterator& n_itr, const std::string& file_data)
{
	std::string read_str;
	for (auto itr = n_itr; itr != file_data.end(); ++itr)
	{
		if (read_str == DATA)
		{
			if (ReadLine(itr, file_data) == ASCII) { m_is_ascii = true; }
			else { m_is_ascii = false; }
			return ++itr;
		}
		read_str.push_back(*itr);
		if (!isEqual(read_str, DATA))
		{
			read_str.clear();
			read_str.shrink_to_fit();
		}
	}
	return file_data.end();
}