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
	m_vertex.emplace_back(ObjectGL::Vertex{ 0.0f, 0.0f,  length});
	m_vertex.emplace_back(ObjectGL::Vertex{ 0.0f, 0.0f, -length});
}