#include "./MyModel.hpp"

MyModel::MyModel():
	m_file_name(DEFAULT_STRING), m_file_extension(DEFAULT_STRING),
	m_vertex_count(0), m_face_count(0),
	is_registration(false)
{

}

MyModel::~MyModel()
{
}
// private
// �t�@�C���p�X����菜��
void MyModel::RegistrationFileIndo(const std::string &file_path)
{
	const char DELIMITER = '\\';
	const char EXTENSION_DELIMITER = '.';

	int first = static_cast<int>(file_path.length());
	int end   = static_cast<int>(file_path.length());
	for (auto itr = file_path.rbegin(); itr != file_path.rend(); ++itr)
	{
		// �g���q�̒T��
		if (*itr == EXTENSION_DELIMITER) { m_file_extension = EXTENSION_DELIMITER + file_path.substr(first, end); }
		// �t�@�C�����̒T��
		if (*itr == DELIMITER)
		{
			m_file_name = file_path.substr(first, end);
			break;
		}
		first--;
	}
}

// public
// ���f���f�[�^�̃��[�h
void MyModel::LoadModelData(const std::string& open_model_data)
{
	// ���O�o�^
	RegistrationFileIndo(open_model_data);

	CubeGL m_cube(5.0f);
	for (int i = 0; i < m_cube.GetVertexSize(); ++i)
	{
		m_model.emplace_back(m_cube.GetVertex()[i]);
	}
	for (int i = 0; i < m_cube.GetIndexSize(); ++i)
	{
		m_index_data.emplace_back(m_cube.GetIndex()[i]);
	}

	// �e��f�[�^�o�^
	is_registration = true;
	m_vertex_count = static_cast<int>(m_model.size());
}