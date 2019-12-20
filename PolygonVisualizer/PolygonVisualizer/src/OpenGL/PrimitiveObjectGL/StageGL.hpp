#ifndef __STAGE_GL_HPP__
#define __STAGE_GL_HPP__

#include "../ObjectGL/ObjectGL.hpp"

#include <GL/glew.h>

#include <vector>

class StageGL
{
	// 定数パラメータ
	// 2点間の距離
	inline static constexpr GLfloat LENGTH = 20.0f;
	inline static constexpr GLfloat MAGNIFICATION = 1.0f;
	inline static constexpr int LINES_NUM = static_cast<int>(LENGTH);

	// 頂点データ
	std::vector<ObjectGL::Vertex> m_vertex;

	// ステージデータ作成
	void MakeStage();
public:
	StageGL();
	~StageGL();

	inline const ObjectGL::Vertex* GetVertex() const { return m_vertex.data(); }
	inline const int GetVertexSize() const { return static_cast<int>(m_vertex.size()); }
};

#endif