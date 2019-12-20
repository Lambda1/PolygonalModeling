#ifndef __MY_MODEL_HPP__
#define __MY_MODEL_HPP__

#include "../OpenGL/ObjectGL/ObjectGL.hpp"
#include "../OpenGL/PrimitiveObjectGL/CubeGL.hpp"

#include <GL/glew.h>

#include <algorithm>
#include <string>
#include <vector>

class MyModel
{
	// �萔�p�����[�^
	inline static const std::string DEFAULT_STRING = "NONE";

	// ��{���f���f�[�^
	std::string m_file_name;         // �t�@�C���l�[��
	std::string m_file_extension;    // �g���q
	int m_vertex_count, m_face_count; // ���_�E�|���S����
	bool is_registration;            // �}�`���o�^����Ă��邩
	// ���_�E�@���f�[�^
	std::vector<ObjectGL::Vertex> m_model;
	// �C���f�b�N�X�f�[�^
	std::vector<GLuint> m_index_data;

	// �t�@�C������o�^
	void RegistrationFileIndo(const std::string &file_path);

public:
	MyModel();
	~MyModel();

	// ���f���f�[�^�ǂݍ���
	void LoadModelData(const std::string &open_model_data);
	// ���f�����o�^����Ă��邩
	inline bool IsRegistration() const { return is_registration; }

	// Getter
	// ���f���f�[�^
	inline const ObjectGL::Vertex* GetModelData() const { return m_model.data(); }
	inline int GetModelDataSize() const { return static_cast<int>(m_model.size()); }
	inline const GLuint* GetIndexData() const { return m_index_data.data(); }
	inline int GetIndexDataSize() const { return static_cast<int>(m_index_data.size()); }
	// ���f���w�b�_
	inline std::string GetFileName() const { return m_file_name; }
	inline const char* GetFileName_C_STR() const { return m_file_name.c_str(); }
};

#endif