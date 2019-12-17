#include "./LightGL.hpp"

LightGL::LightGL():
	m_light_pos{},
	m_light_amb{}, m_light_diff{}, m_light_spec{},
	m_light_id{}
{
}

LightGL::~LightGL()
{
}

void LightGL::SetPos (const GLfloat &x, const GLfloat &y, const GLfloat &z, const GLfloat &w)
{
	m_light_pos[0] = x;
	m_light_pos[1] = y;
	m_light_pos[2] = z;
	m_light_pos[3] = w;
}
void LightGL::SetAmb (const GLfloat &r, const GLfloat &g, const GLfloat &b)
{
	m_light_amb[0] = r;
	m_light_amb[1] = g;
	m_light_amb[2] = b;
}
void LightGL::SetDiff(const GLfloat &r, const GLfloat &g, const GLfloat &b)
{
	m_light_diff[0] = r;
	m_light_diff[1] = g;
	m_light_diff[2] = b;
}
void LightGL::SetSpec(const GLfloat &r, const GLfloat &g, const GLfloat &b)
{
	m_light_spec[0] = r;
	m_light_spec[1] = g;
	m_light_spec[2] = b;
}
