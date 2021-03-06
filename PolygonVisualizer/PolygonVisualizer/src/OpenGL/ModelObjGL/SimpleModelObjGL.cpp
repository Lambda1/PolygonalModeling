#include "./SimpleModelObjGL.hpp"

SimpleModelObjGL::SimpleModelObjGL()
{
}

SimpleModelObjGL::SimpleModelObjGL(const std::string& model_file)
{
	Init(model_file);
}

SimpleModelObjGL::~SimpleModelObjGL()
{

}

/* objファイル読み込み */
void SimpleModelObjGL::Init(const std::string& model_file)
{
	if (m_vertex.capacity() == 0)
	{
		std::ifstream stream_model(model_file);
		ReadVertex(stream_model);
	}
}