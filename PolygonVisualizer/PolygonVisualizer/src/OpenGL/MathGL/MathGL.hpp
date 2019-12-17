#ifndef __MATH_GL_HPP__
#define __MATH_GL_HPP__

/* 変換行列クラス */
/* NOTE: 汎用処理のため, 静的クラス */

#include "../MatrixGL/MatrixGL.hpp"
#include "../VectorGL/VectorGL.hpp"

#include <GL/glew.h>

#include <cmath>
#include <stack>

class MathGL
{
	/* 行列要素 */
	static const int ELEMENT_16; /* 4*4の行列 */
	static const int DIAGONAL_INDEX[4]; /* 対角成分 */

	inline static std::stack<MatrixGL> m_stack;

	public:
		MathGL() = delete;
		void operator=(const MathGL &rhs) = delete;
	static MatrixGL Identity();
	/* 平行移動の変換行列を作成 */
	static MatrixGL Translate(const GLfloat &x, const GLfloat &y, const GLfloat &z);
	static MatrixGL Translate(const GLfloat* vec);
	/* 拡大縮小の変換行列を作成 */
	static MatrixGL Scale(const GLfloat &sx, const GLfloat &sy, const GLfloat &sz);
	/* せん断の変換行列を作成 */
	static MatrixGL Shear(const GLfloat &sx, const GLfloat &sy, const GLfloat &sz);
	/* ロドリゲスの回転公式の変換行列を作成 */
	static MatrixGL RodriguesRotate(const GLfloat &theta,const GLint &nx, const GLint &ny, const GLint &nz);
	/* クォータニオン */
	static MatrixGL Quaternion(const GLfloat &theta,const GLint &nx, const GLint &ny, const GLint &nz);
	
	/* 視点設定 */
	static MatrixGL LookAt
		(
		 const GLfloat &ex, const GLfloat &ey, const GLfloat &ez, /* 視点位置   */
		 const GLfloat &gx, const GLfloat &gy, const GLfloat &gz, /* 注視点位置 */
		 const GLfloat &ux, const GLfloat &uy, const GLfloat &uz  /* 上ベクトル */
		);

	/* 投影変換 */
	/* 直行投影変換 */
	static MatrixGL Orthogonal(const GLfloat &left, const GLfloat &right, const GLfloat &bottom, const GLfloat &top, const GLfloat &z_near, const GLfloat &z_far);
	/* 透視投影の変換行列 */
	static MatrixGL Frustum(const GLfloat &left ,const GLfloat &right,  const GLfloat &bottom, const GLfloat &top, const GLfloat &z_near, const GLfloat z_far);
	/* 透視投影の変換行列(画角ver) */
	static MatrixGL Perspective(const GLfloat &fovy, const GLfloat &aspect, const GLfloat &z_near, const GLfloat &z_far);

	/* 変換行列の保存 */
	inline static void PushMatrix(const MatrixGL &m) { m_stack.push(m); }
	inline static MatrixGL PopMatrix()
	{
		MatrixGL tmp = m_stack.top();
		m_stack.pop();
		return tmp;
	}
};

#endif
