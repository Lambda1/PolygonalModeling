#ifndef __SHAPE_MANAGER_HPP__
#define __SHAPE_MANAGER_HPP__

/* 図形描画クラス */

#include "../OpenGL/ObjectGL/ObjectGL.hpp"
#include "../OpenGL/ShapeGL/ShapeGL.hpp"
#include "../OpenGL/ShapeGL/ShapeGLIndex/ShapeGLIndex.hpp"
#include "../OpenGL/ShapeGL/ShapeGLIndex/ShapeGLIndexSolid.hpp"
#include "../OpenGL/ShapeGL/ShapeGLSolid/ShapeGLSolid.hpp"
#include "../OpenGL/ShapeGL/ShapeGLParticle/ShapeGLParticle.hpp"

#include <memory>
#include <vector>
#include <map>

class ShapeManager
{
	protected:
	std::vector<std::unique_ptr<ShapeGL>> m_shape;

	public:
		ShapeManager();
		virtual ~ShapeManager();

		inline void Draw(const int &index) const
		{
			if (index >= m_shape.size() || index < 0)
			{
				std::cout << "ERROR: SHAPE MANAGER INDEX SIZE IS OUT OF RANGE." << std::endl;
				std::abort();
			}
			if (!m_shape[index])
			{
				std::cout << "ERROR: SHAPE MANAGER'S SHAPEGL IS NULL" << std::endl;
				std::abort();
			}
			m_shape[index]->Draw();
		}

		// 全メモリの解放
		void DiposeMemory();
		// 最後に足されたメモリの解放
		void DiposeMemoryPop();

		/* Setter */
		void SetShape(const ObjectGL::Vertex* data, const int &size,const GLint &position_id, const GLint &normal_id);
		void SetShapeWire(const ObjectGL::Vertex* data, const int& size, const GLint& position_id, const GLint& normal_id);
		void SetShapeWire(const ObjectGL::Vertex* data, const int& size, const GLint& position_id);
		void SetShapeParticle(const ObjectGL::Vertex* data, const int& size, const GLint& position_id);
		void SetShapeWireIndex(const ObjectGL::Vertex* vertex_data, const int& vertex_size, const GLuint* index_data, const GLint& index_size, const GLint& position_id, const GLint& normal_id);

		/* Getter */
		inline const ShapeGL* GetShape(const int& index) const { return m_shape[index].get(); }
};

#endif