#ifndef __MY_MODEL_HPP__
#define __MY_MODEL_HPP__

#include "../OpenGL/ObjectGL/ObjectGL.hpp"
#include "../ModelReader/PCDReader/PCDReader.hpp"
#include "../ModelReader/Bin4Reader/Bin4Reader.hpp"
#include "../OpenGL/MatrixGL/MatrixGL.hpp"
#include "../OpenGL/MathGL/MathGL.hpp"
#include "../OpenGL/PrimitiveObjectGL/CubeGL.hpp"

#include <GL/glew.h>

#include <algorithm>
#include <string>
#include <vector>

class MyModel
{
public:
	enum class MODEL_TYPE
	{
		NONE,
		PARTICLE,
		PARTICLE_COLOR,
		WIRE,
		POLYGON
	};
	// �g���q
	inline static const std::string EXTENSION_PCD = ".pcd";
	inline static const std::string EXTENSION_BIN4 = ".bin4";
private:
	// �萔�p�����[�^
	inline static const std::string DEFAULT_STRING = "NONE";

	// ���f���f�[�^
	ModelReader* m_model_data;
	// ��{���f���f�[�^
	std::string m_file_name;         // �t�@�C���l�[��
	std::string m_file_extension;    // �g���q
	int m_vertex_count, m_face_count; // ���_�E�|���S����
	bool is_registration;            // �}�`���o�^����Ă��邩
	MODEL_TYPE m_model_type;
	// ���_�E�@���f�[�^
	std::vector<ObjectGL::Vertex> m_model;
	// �C���f�b�N�X�f�[�^
	std::vector<GLuint> m_index_data;
	// ���f���s��
	MatrixGL m_model_matrix;
	MatrixGL m_translate, m_scale; // ���s�ړ�, �X�P�[��
	GLfloat m_angle_rad;

	// �t�@�C������o�^
	void RegistrationFileIndo(const std::string &file_path);
	// �f�[�^���`
	void SetVertexParticle(); // ���q�̂�
	void SetVertexParticleColor(); // �_�Q+�F
public:
	MyModel();
	~MyModel();

	// ���f���f�[�^�ǂݍ���
	void LoadModelData(const std::string &open_model_data);
	// ���f�����o�^����Ă��邩
	inline bool IsRegistration() const { return is_registration; }

	// ���f���s��̌v�Z
	inline void CalcModelMatrix(const MatrixGL& view)
	{
		m_model_matrix = view * m_translate * m_scale;
	}

	// Setter
	inline void SetTranslateMatrix(const GLfloat& x, const GLfloat& y, const GLfloat& z) { m_translate = MathGL::Translate(x,y,z); }
	inline void SetFixedScaleMatrix(const GLfloat& scale) { m_scale = MathGL::Scale(scale, scale, scale); }

	// Getter
	// ���f���f�[�^
	inline const ObjectGL::Vertex* GetModelData() const { return m_model.data(); }
	inline int GetModelDataSize() const { return static_cast<int>(m_model.size()); }
	inline const GLuint* GetIndexData() const { return m_index_data.data(); }
	inline int GetIndexDataSize() const { return static_cast<int>(m_index_data.size()); }
	inline MODEL_TYPE GetModelType() const { return m_model_type; }
	// ���f���w�b�_
	inline std::string GetFileName() const { return m_file_name; }
	inline const char* GetFileName_C_STR() const { return m_file_name.c_str(); }
	inline int GetModelFaceNum() const { return m_face_count; }
	inline int GetModelVertexNum() const { return m_vertex_count; }
	// ���f���p��
	inline const MatrixGL& GetModelMatrix() const { return m_model_matrix; }
	inline const GLfloat* GetModelMatrixPtr() const { return m_model_matrix.GetMatrix(); }
	inline void GetModelNormal(GLfloat* normal) const { m_model_matrix.GetNormalMatrix(normal); }
};

#endif