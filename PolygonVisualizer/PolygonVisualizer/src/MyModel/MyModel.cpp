#include "./MyModel.hpp"

MyModel::MyModel() :
	m_model_data(nullptr),
	m_file_name(DEFAULT_STRING), m_file_extension(DEFAULT_STRING),
	m_vertex_count(0), m_face_count(0),
	is_registration(false),
	m_model_type(MODEL_TYPE::NONE)
{
	m_model_matrix.LoadIdentity();
}

MyModel::~MyModel()
{
	if (m_model_data)
	{
		delete m_model_data;
		m_model_data = nullptr;
	}
}
// private
// �t�@�C���p�X����菜��
void MyModel::RegistrationFileIndo(const std::string& file_path)
{
	const char DELIMITER = '\\';
	const char EXTENSION_DELIMITER = '.';

	int first = static_cast<int>(file_path.length());
	int end = static_cast<int>(file_path.length());
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
// �F�Ȃ����q�̓o�^
void MyModel::SetVertexParticle()
{
	constexpr float default_color = 1.0f;
	for (int i = 0; i < m_model_data->GetVertexSize(); ++i)
	{
		m_model.emplace_back(ObjectGL::Vertex
			{
			static_cast<float>(m_model_data->GetVertex()[i].x),
			static_cast<float>(m_model_data->GetVertex()[i].y),
			static_cast<float>(m_model_data->GetVertex()[i].z),
			static_cast<float>(default_color),
			static_cast<float>(default_color),
			static_cast<float>(default_color)
			});
	}
}
// �F���q�̓o�^
void MyModel::SetVertexParticleColor()
{
	for (int i = 0; i < m_model_data->GetVertexColorSize(); ++i)
	{
		m_model.emplace_back(ObjectGL::Vertex
			{
			static_cast<float>(m_model_data->GetVertexColor()[i].x),
			static_cast<float>(m_model_data->GetVertexColor()[i].y),
			static_cast<float>(m_model_data->GetVertexColor()[i].z),
			static_cast<float>(m_model_data->GetVertexColor()[i].r),
			static_cast<float>(m_model_data->GetVertexColor()[i].g),
			static_cast<float>(m_model_data->GetVertexColor()[i].b),
			});
	}
}

// public
// ���f���f�[�^�̃��[�h
void MyModel::LoadModelData(const std::string& open_model_data)
{
	// ���O�o�^
	RegistrationFileIndo(open_model_data);

	// �������J��
	m_model.clear();
	m_model.shrink_to_fit();

	// ���f���ǂݍ���
	// HACK: �e�[�u������ڎw��
	if (m_file_extension == EXTENSION_PCD)
	{
		m_model_type = MODEL_TYPE::PARTICLE;
		m_model_data = new PCDReader(open_model_data);
		SetVertexParticleColor();
	}
	else if (m_file_extension == EXTENSION_BIN4) {
		m_model_type = MODEL_TYPE::PARTICLE;
		m_model_data = new Bin4Reader(open_model_data);
		SetVertexParticleColor();
	}
	else if (m_file_extension == EXTENSION_OBJ) {
		m_model_type = MODEL_TYPE::WIRE;
		m_model_data = new ObjReader(open_model_data);
	}
	else if (m_file_extension == EXTENSION_ASCII) {
		m_model_type = MODEL_TYPE::PARTICLE;
		m_model_data = new AsciiReader(open_model_data);
		SetVertexParticle();
	}

	// �e��f�[�^�o�^
	is_registration = true;
	m_vertex_count = static_cast<int>(m_model.size());
}