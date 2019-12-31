#include "./AsciiReader.hpp"

AsciiReader::AsciiReader(const std::string& open_file_path)
{
	ReadFile(open_file_path);
}

AsciiReader::~AsciiReader()
{

}

// private
void AsciiReader::ReadFile(const std::string& open_file_path)
{
	std::ifstream file_stream(open_file_path, std::ios::in | std::ios::binary);
	if (file_stream.fail())
	{
		std::cerr << "ERROR: CANNOT READ PCD FILE." << std::endl;
		std::cerr << __FILE__ << " " << __LINE__ << std::endl;
		std::abort();
	}
	ReadData(file_stream);
}
// 空白区切り読み込み
// NOTE: 1バイトずつ処理
void AsciiReader::ReadData(std::ifstream& file_data)
{
	std::vector<float> data;
	std::string num;
	char buff;
	while (true)
	{
		file_data.read(&buff, sizeof(char));
		
		// read -> eofの順番で判定されるため, ここでEoFの処理
		if (file_data.eof()) { break; }

		// 数値としてスタックする
		if (buff != ' ' && buff != '\n') { num.push_back(buff); }
		else { data.emplace_back(std::stof(num)); num.clear(); }
	}
	// vertexに座標を保存
	for (int i = 0; i+3 < static_cast<int>(data.size()); i+=3)
	{
		m_vertex.emplace_back(Vector{ data[i + 0], data[i + 1], data[i + 2] });
	}
}