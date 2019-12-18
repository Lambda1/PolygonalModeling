#include "./CubeGL.hpp"

CubeGL::CubeGL()
{
	Make(1.0f);
	MakeIndex();
}

CubeGL::CubeGL(const GLfloat &rate)
{
	Make(rate);
	MakeIndex();
}

CubeGL::~CubeGL()
{
}

void CubeGL::Make(const GLfloat &rate)
{
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length,-length, -1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length, length, -1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length, length, -1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length,-length, -1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length, length, -1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length,-length, -1.0f, 0.0f, 0.0f});

	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length,-length, 0.0f, 0.0f, -1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length,-length, 0.0f, 0.0f, -1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length,-length, 0.0f, 0.0f, -1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length,-length, 0.0f, 0.0f, -1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length,-length, 0.0f, 0.0f, -1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length,-length, 0.0f, 0.0f, -1.0f});

	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length,-length, 0.0f, -1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length,-length, 0.0f, -1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length, length, 0.0f, -1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length,-length, 0.0f, -1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length, length, 0.0f, -1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length, length, 0.0f, -1.0f, 0.0f});

	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length, length, 1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length,-length, 1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length,-length, 1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length, length, 1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length,-length, 1.0f, 0.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length, length, 1.0f, 0.0f, 0.0f});

	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length,-length, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length, length, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length, length, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length,-length, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length, length, 0.0f, 1.0f, 0.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length,-length, 0.0f, 1.0f, 0.0f});

	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length, length, 0.0f, 0.0f, 1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate,-length, length, 0.0f, 0.0f, 1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length, length, 0.0f, 0.0f, 1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate,-length, length, 0.0f, 0.0f, 1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{ length*rate, length, length, 0.0f, 0.0f, 1.0f});
	m_vertex.emplace_back(ObjectGL::Vertex{-length*rate, length, length, 0.0f, 0.0f, 1.0f});
}

void CubeGL::MakeIndex()
{
	for(int i = 0;i < vertex_num;++i)
	{
		m_index.emplace_back(i);
	}
}
