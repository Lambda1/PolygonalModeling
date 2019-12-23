#include "./Bin4Reader.hpp"

Bin4Reader::Bin4Reader(const std::string& open_file_path):
	m_vec_num(0)
{
	ReadFile(open_file_path);
}

Bin4Reader::~Bin4Reader()
{
}

// private
void Bin4Reader::ReadFile(const std::string& open_file_path)
{
	std::ifstream file_data(open_file_path, std::ios::in | std::ios::binary);

	// �ǂݍ��ݎ��s
	if (file_data.fail()) { std::cerr << "ERROR: CANNOT OPEN " << open_file_path << "." << std::endl; return; }
	
	// �w�b�_�ǂݍ���
	ReadHeader(file_data);
	
	// �f�[�^�ǂݍ���
	if (m_vec_num == BASE_VECTOR) { ReadDataNormalFormat(file_data); }
	else if (m_vec_num == POINTS_VECTOR) { ReadDataOnlyPoint(file_data); }

	// �ǂݍ��ݐ���
	is_read_success = true;
	file_data.close();
}
void Bin4Reader::ReadHeader(std::ifstream& file_stream)
{
	BYTE_4 header;
	
	// �w�b�_��4�o�C�g�ǂݍ���
	if (!file_stream.eof())
	{
		file_stream.read(reinterpret_cast<char*>(&header), sizeof(BYTE_4));
		m_vec_num = static_cast<int>(header);
	}
}
// �ʏ�`����7�x�N�g���ǂݍ���
// NOTE: ��x���ׂēǂݍ���ł���x�N�g��������U��
void Bin4Reader::ReadDataNormalFormat(std::ifstream& file_stream)
{
	// �t�@�C���ǂݎ��
	std::vector<BYTE_4> read_data;
	BYTE_4 temp_data;
	while (!file_stream.eof())
	{
		file_stream.read(reinterpret_cast<char*>(&temp_data), sizeof(BYTE_4));
		read_data.emplace_back(temp_data);
	}

	// �f�[�^�z�u
	for (int i = 0; i+(BASE_VECTOR-1) < static_cast<int>(read_data.size()); i += BASE_VECTOR)
	{
		// x, y, z
		// r, g, b, a
		m_vertex_color.emplace_back(VectorColor
			{
				read_data[i+0], read_data[i+1], read_data[i+2],
				read_data[i+3], read_data[i+4], read_data[i+5], read_data[i+6]
			});
	}
	is_color = true;
}
// �_�Q�f�[�^�̂�
void Bin4Reader::ReadDataOnlyPoint(std::ifstream& file_stream)
{
	// �t�@�C���ǂݎ��
	std::vector<BYTE_4> read_data;
	BYTE_4 temp_data;
	while (!file_stream.eof())
	{
		file_stream.read(reinterpret_cast<char*>(&temp_data), sizeof(BYTE_4));
		read_data.emplace_back(temp_data);
	}

	// �f�[�^�z�u
	for (int i = 0; i + (POINTS_VECTOR - 1) < static_cast<int>(read_data.size()); i += POINTS_VECTOR)
	{
		// x, y, z
		m_vertex.emplace_back(Vector { read_data[i + 0], read_data[i + 1], read_data[i + 2] });
	}
}