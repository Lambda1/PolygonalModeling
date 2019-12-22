#ifndef __MODEL_READER_HPP__
#define __MODEL_READER_HPP__

#include <string>
#include <vector>

class ModelReader
{
public:
	struct Vector { double x, y, z; };
	struct VectorColor : public Vector { double r, g, b, alpha; };
protected:
	std::vector<Vector> m_vertex;
	std::vector<VectorColor> m_vertex_color;

	size_t m_file_size;

	virtual void ReadFile(const std::string& open_file_path) = 0;
public:
	ModelReader() :
		m_file_size(0)
	{
	}
	virtual ~ModelReader()
	{
	}

	// Getter
	inline const Vector* GetVertex() const { return m_vertex.data(); }
	inline int GetVertexSize() const { return static_cast<int>(m_vertex.size()); }
	inline const VectorColor* GetVertexColor() const { return m_vertex_color.data(); }
	inline int GetVertexColorSize() const { return static_cast<int>(m_vertex_color.size()); }
};

#endif