#include "./MathGL.hpp"

const int MathGL::ELEMENT_16 = 16; /* 4*4の行列 */
const int MathGL::DIAGONAL_INDEX[4] = {0, 5, 10, 15}; /* 対角成分 */

/* アフィン変換 */
/* NOTE: 効率化を重視して, 共通処理とする. */
/* 単位行列を作成 */
MatrixGL MathGL::Identity()
{
	MatrixGL matrix;
	matrix.LoadIdentity();
	return matrix;
}

/* 平行移動の変換行列を作成 */
MatrixGL MathGL::Translate(const GLfloat &x, const GLfloat &y, const GLfloat &z)
{
	MatrixGL matrix;
	matrix.LoadIdentity();
	matrix[12] = x;
	matrix[13] = y;
	matrix[14] = z;
	return matrix;
}
/* ベクトル版  */
MatrixGL MathGL::Translate(const GLfloat* vec)
{
	MatrixGL matrix;
	matrix.LoadIdentity();
	matrix[12] = vec[0];
	matrix[13] = vec[1];
	matrix[14] = vec[2];
	return matrix;
}

/* 拡大縮小の変換行列を作成 */
MatrixGL MathGL::Scale(const GLfloat &sx, const GLfloat &sy, const GLfloat &sz)
{
	MatrixGL matrix;
	matrix.LoadIdentity();
	matrix[DIAGONAL_INDEX[0]] = sx;
	matrix[DIAGONAL_INDEX[1]] = sy;
	matrix[DIAGONAL_INDEX[2]] = sz;
	return matrix;
}
/* せん断の変換行列を作成 */
MatrixGL MathGL::Shear(const GLfloat &sx, const GLfloat &sy, const GLfloat &sz)
{
	MatrixGL matrix;
	matrix.LoadIdentity();
	return matrix;
}
/* ロドリゲスの回転公式の変換行列を作成 */
MatrixGL MathGL::RodriguesRotate(const GLfloat &theta,const GLint &nx, const GLint &ny, const GLint &nz)
{
	MatrixGL matrix;
	matrix.LoadIdentity();
	const GLfloat sinf = std::sin(theta), cosf = std::cos(theta);

	matrix[0]  = cosf+nx*nx*(1.0f-cosf);
	matrix[4]  = nx*ny*(1.0f-cosf)+nz*sinf;
	matrix[8]  = nx*nz*(1.0f-cosf)-ny*sinf;

	matrix[1]  = nx*ny*(1.0f-cosf)-nz*sinf;
	matrix[5]  = cosf+ny*ny*(1.0f-cosf);
	matrix[9]  = ny*nz*(1.0f-cosf)+nx*sinf;

	matrix[2]  = nx*nz*(1.0f-cosf)+ny*sinf;
	matrix[6]  = ny*nz*(1.0f-cosf)-nx*sinf;
	matrix[10] = cosf+nz*nz*(1.0f-cosf);

	return matrix;
}
MatrixGL MathGL::Quaternion(const GLfloat &theta,const GLint &nx, const GLint &ny, const GLint &nz)
{
	GLfloat sinf = std::sin(theta/2.0f);
	GLfloat x = nx*sinf, y = ny*sinf, z = nz*sinf, w = std::cos(theta/2.0f);

	MatrixGL matrix;

	matrix[0] = x*x - y*y - z*z + w*w;
	matrix[1] = 2.0f*x*y - 2.0f*w*z;
	matrix[2] = 2.0f*x*z + 2.0f*w*y;
	matrix[3] = 0.0f;

	matrix[4] = 2.0f*x*y + 2.0f*w*z;
	matrix[5] = -x*x + y*y - z*z + w*w;
	matrix[6] = 2.0f*y*z - 2.0f*w*x;
	matrix[7] = 0.0f;
	
	matrix[8] = 2.0f*x*z - 2.0f*w*y;
	matrix[9] = 2.0f*y*z + 2.0f*w*x;
	matrix[10] = -x*x - y*y + z*z + w*w;
	matrix[11] = 0.0f;
	
	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	return matrix;
}

/* 汎用処理 */
/* NOTE: 共通化のため, 静的メンバで定義. */
/* 視点設定 */
MatrixGL MathGL::LookAt
(
 const GLfloat &ex, const GLfloat &ey, const GLfloat &ez, /* 視点位置   */
 const GLfloat &gx, const GLfloat &gy, const GLfloat &gz, /* 注視点位置 */
 const GLfloat &ux, const GLfloat &uy, const GLfloat &uz  /* 上ベクトル */
 )
{
	/* 視点を原点へ平行移動 */
	const MatrixGL matrix(Translate(-ex, -ey, -ez));

	/* t軸(視点座標系におけるz軸) */
	/* NOTE: t = e-g*/
	const GLfloat tx(ex - gx);
	const GLfloat ty(ey - gy);
	const GLfloat tz(ez - gz);

	/* r軸(視点座標系におけるx軸) */
	/* NOTE: r = u*t (外積) */
	const GLfloat rx(uy*tz - uz*ty);
	const GLfloat ry(uz*tx - ux*tz);
	const GLfloat rz(ux*ty - uy*tx);

	/* s軸(視点座標系におけるy軸) */
	/* NOTE: s = t*r (外積) */
	const GLfloat sx(ty*rz - tz*ry);
	const GLfloat sy(tz*rx - tx*rz);
	const GLfloat sz(tx*ry - ty*rx);

	/* s軸の長さチェック */
	const GLfloat s_len(sx*sx+sy*sy+sz*sz);
	if(s_len == 0.0f) return matrix;

	/* 回転の変換行列 */
	MatrixGL rotate_v;
	rotate_v.LoadIdentity();

	/* r軸を正規化して格納 */
	const GLfloat r(std::sqrt(rx*rx + ry*ry + rz*rz));
	rotate_v[0] = rx / r;
	rotate_v[4] = ry / r;
	rotate_v[8] = rz / r;

	/* s軸を正規化して格納 */
	const GLfloat s(std::sqrt(s_len));
	rotate_v[1] = sx / s;
	rotate_v[5] = sy / s;
	rotate_v[9] = sz / s;

	/* t軸を正規化して格納 */
	const GLfloat t(std::sqrt(tx*tx + ty*ty + tz*tz));
	rotate_v[2]  = tx / t;
	rotate_v[6]  = ty / t;
	rotate_v[10] = tz / t;

	/* ビュー変換行列の算出 */
	return rotate_v * matrix;
}
/* 直行投影変換 */
MatrixGL MathGL::Orthogonal
(
 const GLfloat &left, const GLfloat &right,
 const GLfloat &bottom, const GLfloat &top,
 const GLfloat &z_near, const GLfloat &z_far
 )
{
	MatrixGL matrix;
	const GLfloat dx(right - left);
	const GLfloat dy(top - bottom);
	const GLfloat dz(z_far - z_near);

	matrix.LoadIdentity();

	if(dx == 0.0f || dy == 0.0f || dz == 0.0f) return matrix;

	/* 対角成分の定義 */
	matrix[DIAGONAL_INDEX[0]] = 2.0f / dx;
	matrix[DIAGONAL_INDEX[1]] = 2.0f / dy;
	matrix[DIAGONAL_INDEX[2]] = -(2.0f / dz);
	/* 4列目の定義 */
	matrix[12] = -(right + left)/dx;
	matrix[13] = -(top + bottom)/dy;
	matrix[14] = -(z_far + z_near)/dz;
	return matrix;
}
/* 透視投影の変換行列 */
MatrixGL MathGL::Frustum
(
 const GLfloat &left ,const GLfloat &right,
 const GLfloat &bottom, const GLfloat &top,
 const GLfloat &z_near, const GLfloat z_far
 )
{
	MatrixGL matrix;
	const GLfloat dx(right-left);
	const GLfloat dy(top-bottom);
	const GLfloat dz(z_far-z_near);

	matrix.LoadIdentity();
	if(dx == 0.0f || dy == 0.0f || dz == 0.0f) return matrix;

	/* 対角成分の定義 */
	matrix[DIAGONAL_INDEX[0]] = 2.0f * z_near / dx;
	matrix[DIAGONAL_INDEX[1]] = 2.0f * z_near / dy;
	matrix[DIAGONAL_INDEX[2]] = -(z_far + z_near) / dz;
	matrix[DIAGONAL_INDEX[3]] = 0.0f; 
	/* 3列目の定義 */
	matrix[8]  = (right+left)/dx;
	matrix[9]  = (top+bottom)/dy;
	matrix[11] = -1.0f;
	/* 4列目の定義 */
	matrix[14] = -(2.0f * z_far * z_near)/dz;

	return matrix;
}
/* 透視投影の変換行列(画角ver) */
MatrixGL MathGL::Perspective(const GLfloat &fovy, const GLfloat &aspect, const GLfloat &z_near, const GLfloat &z_far)
{
	MatrixGL matrix;
	const GLfloat dz(z_far - z_near);

	matrix.LoadIdentity();
	if(dz == 0.0f) return matrix;

	/* 対角成分 */
	matrix[DIAGONAL_INDEX[1]] = 1.0f/tan(fovy/2.0f); /* cot(fovy/2.0f) */
	matrix[DIAGONAL_INDEX[0]] = matrix[DIAGONAL_INDEX[1]] / aspect;
	matrix[DIAGONAL_INDEX[2]] = -(z_far+z_near)/dz;
	matrix[DIAGONAL_INDEX[3]] = 0.0f;

	matrix[11] = -1.0f;
	matrix[14] = -(2.0f * z_far * z_near)/dz;

	return matrix;
}
