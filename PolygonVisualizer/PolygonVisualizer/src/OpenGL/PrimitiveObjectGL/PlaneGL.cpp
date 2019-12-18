#include "./PlaneGL.hpp"

PlaneGL::PlaneGL()
{
	Make(1.0f);
	MakeIndex();
}

PlaneGL::PlaneGL(const GLfloat &rate)
{
	Make(rate);
	MakeIndex();
}

PlaneGL::~PlaneGL()
{
}

void PlaneGL::Make(const GLfloat &rate)
{
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,0,-length*rate, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,0, length*rate, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,0, length*rate, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,0,-length*rate, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,0, length*rate, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,0,-length*rate, 0.0f, 1.0f, 0.0f});
}
	
void PlaneGL::MakeIndex()
{
	for(int i = 0;i < vertex_num;++i)
	{
		m_index.emplace_back(i);
	}
}
