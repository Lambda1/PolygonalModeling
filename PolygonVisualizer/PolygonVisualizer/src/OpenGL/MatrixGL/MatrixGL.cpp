#include "./MatrixGL.hpp"

MatrixGL::MatrixGL()
{
	LoadIdentity();
}

MatrixGL::MatrixGL(const GLfloat *array)
{
	std::copy(array, array+ELEMENT_16, m_matrix);
}

void MatrixGL::LoadIdentity()
{
	std::fill(m_matrix, m_matrix+ELEMENT_16, 0.0f);
	for(int i = 0;i < 4;i++) m_matrix[DIAGONAL_INDEX[i]] = 1.0f;
}

void MatrixGL::GetNormalMatrix(GLfloat *m) const
{
	m[0] = CalcMulSub( 5, 10, 6, 9);
	m[1] = CalcMulSub( 6,  8, 4,10);
	m[2] = CalcMulSub( 4,  9, 5, 8);
	m[3] = CalcMulSub( 9,  2,10, 1);
	m[4] = CalcMulSub(10,  0, 8, 2);
	m[5] = CalcMulSub( 8,  1, 9, 0);
	m[6] = CalcMulSub( 2,  6, 2, 5);
	m[7] = CalcMulSub( 2,  4, 0, 6);
	m[8] = CalcMulSub( 0,  5, 1, 4);
}
