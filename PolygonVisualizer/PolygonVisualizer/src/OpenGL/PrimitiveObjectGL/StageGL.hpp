#ifndef __STAGE_GL_HPP__
#define __STAGE_GL_HPP__

#include "../ObjectGL/ObjectGL.hpp"

#include <GL/glew.h>

#include <vector>

class StageGL
{
	// 定数パラメータ
	// 2点間の距離
	inline static constexpr GLfloat length = 10000.0f;
	inline static constexpr int POINTS_NUM = 2;

	// 頂点データ
	std::vector<ObjectGL::Vertex> m_vertex;

	// ステージデータ作成
	void MakeStage();
public:
	StageGL();
	~StageGL();

	inline const ObjectGL::Vertex* GetVertex() const { return m_vertex.data(); }
	inline const int GetVertexSize() const { return POINTS_NUM; }
};

#endif