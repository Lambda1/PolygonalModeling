#ifndef __MODEL_READER_HPP__
#define __MODEL_READER_HPP__

#include <string>
#include <vector>

class ModelReader
{
public:
	struct Vector { double x, y, z; };
protected:
	std::vector<Vector> m_vertex;

	virtual void ReadFile(const std::string& open_file_path) = 0;
public:
	virtual ~ModelReader()
	{
	}

	// Getter
	inline const Vector* GetVertex() const { return m_vertex.data(); }
	inline int GetVertexSize() const { return static_cast<int>(m_vertex.size()); }
};

#endif