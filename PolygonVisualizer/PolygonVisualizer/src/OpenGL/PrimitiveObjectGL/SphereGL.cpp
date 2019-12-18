#include "./SphereGL.hpp"

void SphereGL::Make()
{
	for(int i = 0; i <= m_stacks;++i)
	{
		const float t = static_cast<float>(i) / static_cast<float>(m_stacks);
		const float y = std::cos(PI * t), r = std::sin(PI * t);
		for(int j = 0;j <= m_slices; ++j)
		{
			const float s = static_cast<float>(j) / static_cast<float>(m_slices);
			const float z = r * std::cos(PI*2.0f*s), x = r*std::sin(PI*2.0f*s);

			const ObjectGL::Vertex v = {x, y, z, x, y, z};
			m_vertex.emplace_back(v);
		}
	}
}

void SphereGL::MakeIndex()
{
	for(int i = 0;i < m_stacks;++i)
	{
		const int k = (m_slices+1) * i;
		for(int j = 0;j < m_slices;++j)
		{
			const GLuint k0 = k  + j;
			const GLuint k1 = k0 + 1;
			const GLuint k2 = k1 + m_slices;
			const GLuint k3 = k2 + 1;

			m_index.emplace_back(k0);
			m_index.emplace_back(k2);
			m_index.emplace_back(k3);

			m_index.emplace_back(k0);
			m_index.emplace_back(k3);
			m_index.emplace_back(k1);
		}
	}
}
