#ifndef __LIGHT_GL_HPP__
#define __LIGHT_GL_HPP__

/* 光源データ  */

#include "../MatrixGL/MatrixGL.hpp"
#include "../VectorGL/VectorGL.hpp"

#include <GL/glew.h>

namespace LightGLFunc
{
	enum class TYPE : int
	{
		POSITION,
		AMBIENT,
		DIFFUSE,
		SPECULAR,

		SIZE
	};
	inline static int TransID(const LightGLFunc::TYPE &id){ return static_cast<int>(id); }
};

class LightGL
{
	/* 次元定義 */
	inline static constexpr int m_light_dim = 4; /* 同次座標 */
	inline static constexpr int m_light_ref = 3; /* RGB */
	inline static constexpr int m_light_num = 4; /* ライトの種類 */

	VectorGL::Vector m_light_pos;      /* 光源位置 */
	GLfloat m_light_amb[m_light_ref];  /* 環境光 */
	GLfloat m_light_diff[m_light_ref]; /* 拡散反射光 */
	GLfloat m_light_spec[m_light_ref]; /* 鏡面反射光 */

	GLint m_light_id[m_light_num]; /* シェーダID */

	public:	
	LightGL();
	~LightGL();

	/* Setter */
	void SetPos (const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w);
	void SetAmb (const GLfloat &r, const GLfloat &g, const GLfloat &b);
	void SetDiff(const GLfloat &r, const GLfloat &g, const GLfloat &b);
	void SetSpec(const GLfloat &r, const GLfloat &g, const GLfloat &b);
	void SetID(const GLint *id, const int &bias){ for(int i = 0;i < m_light_num;++i){ m_light_id[i] = id[i]+bias; } }

	/* Getter */
	const VectorGL::Vector &GetPos()  const { return m_light_pos; }
	const GLfloat *GetAmb()  const { return m_light_amb; }
	const GLfloat *GetDiff() const { return m_light_diff; }
	const GLfloat *GetSpec() const { return m_light_spec; }
	const GLint GetID(const int &id) const { return m_light_id[id]; }
};

#endif
