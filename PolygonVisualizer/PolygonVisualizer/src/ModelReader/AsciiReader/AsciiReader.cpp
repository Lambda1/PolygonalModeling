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
	char buff = 0;

	// RGB or BIN 判定
	int count = 0;
	while (buff != '\n')
	{
		file_data.read(&buff, sizeof(char));
		if (buff == ' ') count++;
	}
	std::cout << "COUNT: " << count << std::endl;
	// 先頭までシーク
	file_data.seekg(0, std::ios_base::beg);
	
	// 読み込み
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
	if (count == RGB_VERTEX_COUNT) { SendVertexColor(data); }
	else { SendVertex(data); }
}
// 色付きデータを形成
void AsciiReader::SendVertexColor(const std::vector<float>& data)
{
	constexpr int next_data_bias = 6;
	constexpr int read_data_bias = 5;
	for (int i = 0; i + read_data_bias <= static_cast<int>(data.size()); i += next_data_bias)
	{
		m_vertex_color.emplace_back(VectorColor
			{
				data[i + 0], data[i + 1], data[i + 2],
				data[i + 3], data[i + 4], data[i + 5]
			});
	}
}
// PCDのみ
void AsciiReader::SendVertex(const std::vector<float>& data)
{
	constexpr int next_data_bias = 3;
	constexpr int read_data_bias = 2;
	for (int i = 0; i + read_data_bias <= static_cast<int>(data.size()); i += next_data_bias)
	{
		m_vertex_color.emplace_back(VectorColor
			{
				data[i + 0], data[i + 1], data[i + 2],
				DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR
			});
	}
}