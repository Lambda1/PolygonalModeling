#ifndef __STAGE_GL_HPP__
#define __STAGE_GL_HPP__

#include "../ObjectGL/ObjectGL.hpp"

#include <GL/glew.h>

#include <vector>

class StageGL
{
	// �萔�p�����[�^
	// 2�_�Ԃ̋���
	inline static constexpr GLfloat length = 10000.0f;
	inline static constexpr int POINTS_NUM = 2;

	// ���_�f�[�^
	std::vector<ObjectGL::Vertex> m_vertex;

	// �X�e�[�W�f�[�^�쐬
	void MakeStage();
public:
	StageGL();
	~StageGL();

	inline const ObjectGL::Vertex* GetVertex() const { return m_vertex.data(); }
	inline const int GetVertexSize() const { return POINTS_NUM; }
};

#endif