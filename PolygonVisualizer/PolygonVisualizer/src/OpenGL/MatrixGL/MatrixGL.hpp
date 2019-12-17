#ifndef __MATRIX_GL_HPP__
#define __MATRIX_GL_HPP__

#include "../VectorGL/VectorGL.hpp"

#include <GL/glew.h>

#include <cmath>
#include <algorithm>

class MatrixGL
{
	/* 行列要素 */
	inline static constexpr int ELEMENT_16 = 16; /* 4*4の行列 */
	inline static constexpr int DIAGONAL_INDEX[4] = {0, 5, 10, 15}; /* 対角成分 */

	/* 変換行列の要素 */
	GLfloat m_matrix[ELEMENT_16]; /* 同時座標系 */
	public:
	MatrixGL();
	MatrixGL(const GLfloat *array); /* array: 4*4の配列 */

	/* 変換関数群 */
	inline GLfloat CalcMulSub(const int &v1_1,const int &v1_2, const int &v2_1, const int &v2_2) const { return m_matrix[v1_1]*m_matrix[v1_2] - m_matrix[v2_1]*m_matrix[v2_2]; }

	/* 単位行列を設定 */
	void LoadIdentity();

	/* Operator */
	/* 行列式の定義 */
	MatrixGL operator*(const MatrixGL &rhs) const
	{
		MatrixGL tmp;

		for(int i = 0;i < ELEMENT_16;++i)
		{
			const int j(i&3), k(i&~3);
			tmp.m_matrix[i] = 
				m_matrix[ 0+j] * rhs.m_matrix[k+0] + 
				m_matrix[ 4+j] * rhs.m_matrix[k+1] + 
				m_matrix[ 8+j] * rhs.m_matrix[k+2] + 
				m_matrix[12+j] * rhs.m_matrix[k+3];
		}

		return tmp;
	}
	/* 行列とベクトルの積 */
	inline VectorGL::Vector operator*(const VectorGL::Vector &rhs)
	{
		VectorGL::Vector tmp;

		for(int i = 0;i < VectorGL::m_dim;i++)
		{
			tmp[i] = m_matrix[i] * rhs[0] + m_matrix[i+4] * rhs[1] + m_matrix[i+8] * rhs[2] + m_matrix[i+12] * rhs[3];
		}
		return tmp;
	}
	inline VectorGL::Vector operator*(const VectorGL::Vector& rhs) const
	{
		VectorGL::Vector tmp;

		for (int i = 0; i < VectorGL::m_dim; i++)
		{
			tmp[i] = m_matrix[i] * rhs[0] + m_matrix[i + 4] * rhs[1] + m_matrix[i + 8] * rhs[2] + m_matrix[i + 12] * rhs[3];
		}
		return tmp;
	}
	const GLfloat &operator[](const int &i) const { return m_matrix[i]; }
	GLfloat &operator[](const int &i) { return m_matrix[i]; }

	/* Getter */
	inline const GLfloat *GetMatrix() const { return m_matrix; }
	void GetNormalMatrix(GLfloat *m) const; /* 法線ベクトルの変換行列 */
};

#endif
