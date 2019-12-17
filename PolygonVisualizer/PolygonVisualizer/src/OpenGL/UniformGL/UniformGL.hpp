#ifndef __UNIFORM_GL_HPP__
#define __UNIFORM_GL_HPP__

#include "../../DebugInfo.hpp"

#include <memory>
#include <GL/glew.h>

template<class T>
class UniformGL
{
	/* UBOデータ構造の定義 */
	struct UniformBuffer
	{
		GLuint m_ubo;
		GLsizeiptr m_block_size; /* ユニフォームブロックサイズ */

		/* 格納データ, 確保するブロック数 */
		UniformBuffer(const T *data, const unsigned int &count):
			m_ubo(0), m_block_size(0)
		{
			/* ユニフォームブロックサイズ決定 */
			GLint alignment;
			glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &alignment);
			m_block_size = ((sizeof(T)-1)/alignment+1)*alignment;
			/* ユニフォームバッファ作成 */
			glGenBuffers(1, &m_ubo);
			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			glBufferData(GL_UNIFORM_BUFFER, count*m_block_size, nullptr, GL_STATIC_DRAW);
			for(unsigned int i = 0;i < count;++i)
			{
				glBufferSubData(GL_UNIFORM_BUFFER, i*m_block_size, sizeof(T), data+i);
			}

#if DEBUG
			std::cout << "UBO :" << m_ubo << std::endl;
#endif

		}
		~UniformBuffer()
		{
			glDeleteBuffers(1, &m_ubo);
		}
	};
	/* UBO */
	const std::shared_ptr<const UniformBuffer> m_buffer;
	
	public:
	/* 格納データ, ブロック数 */
	UniformGL(const T *data = nullptr,unsigned int count = 1):
		m_buffer(new UniformBuffer(data,count))
	{
	}
	virtual ~UniformGL()
	{
	}
	/* 格納データ, 先頭位置, ブロック数 */
	void Set(const T *data,const unsigned int &start = 0,const unsigned int &count = 1) const
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_buffer->m_ubo);
		for(unsigned int i = 0;i < count;++i)
		{
			glBufferSubData(GL_UNIFORM_BUFFER, (start+i)*m_buffer->m_block_size, sizeof(T), data+i);
		}
	}
	/* 結合ポイント, ブロック位置 */
	void Select(const GLuint &bp, const unsigned int &i=0) const
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, bp, m_buffer->m_ubo, i*m_buffer->m_block_size, sizeof(T));
	}
};

#endif
