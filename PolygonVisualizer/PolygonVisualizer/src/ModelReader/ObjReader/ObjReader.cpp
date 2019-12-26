#include "./ObjReader.hpp"

ObjReader::ObjReader(const std::string& open_file_path)
{
	ReadFile(open_file_path);
}

ObjReader::~ObjReader()
{
}

// private
// NOTE: シェーディングを仮定しない
void ObjReader::ReadFile(const std::string& open_file_path)
{
	std::ifstream file_data(open_file_path, std::ios::in);
	// 読み込み失敗
	if (file_data.fail()) { std::cerr << "ERROR: CANNOT OPEN " << open_file_path << "." << std::endl; return; }

	// 頂点読み込み
	std::vector<ModelReader::Vector> vertex = ReadVertex(file_data);

	is_read_success = true;
}
// 
std::vector<ModelReader::Vector> ObjReader::ReadVertex(std::ifstream& file_data)
{
	std::vector<Vector> m_vertex;
	
	std::string buffer;
	while (std::getline(file_data, buffer))
	{
		for (auto itr = buffer.begin(); itr != buffer.end(); ++itr)
		{

		}
		int head_pos = buffer.find(OBJ_FORMAT_DELIMITER);
		if (buffer[0] == OBJ_FORMAT_COMMENT) { continue; }
		if (buffer[0] != 'v') { break; }
		std::cout << buffer << std::endl;
	}

	return m_vertex;
}
// 一行読み込み
// NOTE: 初めの空白までを読み飛ばす
ModelReader::Vector ObjReader::ReadLineData(std::string& buffer)
{
	ModelReader::Vector data;
	int head_pos = buffer.find(OBJ_FORMAT_DELIMITER);

	buffer = buffer.substr(0, head_pos+1);

	return data;
}