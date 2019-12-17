#include "./ObjectGL.hpp"

ObjectGL::ObjectGL(const GLsizei v_count,const Vertex *vertex, const GLsizei index_count, const GLuint *index) :
	m_vao(0), m_vbo(0), m_ibo(0)
{
	/* VAO */
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	/* VBO */
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, v_count*sizeof(Vertex), vertex, GL_STATIC_DRAW);

	/* IBO */
	glGenBuffers(1, &m_ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count*sizeof(GLuint), index, GL_STATIC_DRAW);

#if DEBUG
	std::cerr << m_vao << " " << m_vbo << " " << m_ibo << std::endl;
#endif
}

ObjectGL::~ObjectGL()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ibo);
}
