#include "./StageGL.hpp"

StageGL::StageGL()
{
	MakeStage();
}

StageGL::~StageGL()
{
}

// private
void StageGL::MakeStage()
{
	for (int i = -LINES_NUM; i <= LINES_NUM; ++i)
	{
		m_vertex.emplace_back(ObjectGL::Vertex{ MAGNIFICATION * i, 0.0f,  LENGTH });
		m_vertex.emplace_back(ObjectGL::Vertex{ MAGNIFICATION * i, 0.0f, -LENGTH });

		m_vertex.emplace_back(ObjectGL::Vertex{  LENGTH, 0.0f, MAGNIFICATION * i });
		m_vertex.emplace_back(ObjectGL::Vertex{ -LENGTH, 0.0f, MAGNIFICATION * i });
	}
}