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
// �󔒋�؂�ǂݍ���
// NOTE: 1�o�C�g������
void AsciiReader::ReadData(std::ifstream& file_data)
{
	std::vector<float> data;
	std::string num;
	char buff;
	while (true)
	{
		file_data.read(&buff, sizeof(char));
		
		// read -> eof�̏��ԂŔ��肳��邽��, ������EoF�̏���
		if (file_data.eof()) { break; }

		// ���l�Ƃ��ăX�^�b�N����
		if (buff != ' ' && buff != '\n') { num.push_back(buff); }
		else { data.emplace_back(std::stof(num)); num.clear(); }
	}
	// vertex�ɍ��W��ۑ�
	for (int i = 0; i+5 <= static_cast<int>(data.size()); i+=6)
	{
		m_vertex_color.emplace_back(VectorColor
			{
				data[i + 0]*0.0001, data[i + 1]*0.0001, data[i + 2]*0.0001,
				data[i + 3], data[i + 4], data[i + 5]
			});
	}
	/*
	// vertex�ɍ��W��ۑ�
	for (int i = 0; i + 3 < static_cast<int>(data.size()); i += 3)
	{
		m_vertex_color.emplace_back(VectorColor
			{
				data[i + 0], data[i + 1], data[i + 2],
				DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR, DEFAULT_COLOR
			});
	}
	*/
}