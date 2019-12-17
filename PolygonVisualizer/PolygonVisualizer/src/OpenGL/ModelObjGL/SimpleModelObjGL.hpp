#ifndef __SIMPLE_MODEL_OBJ_GL_HPP__
#define __SIMPLE_MODEL_OBJ_GL_HPP__

/*
	.objファイルの読み込みのみを行う.
*/

#include "./ModelObjGL.hpp"

class SimpleModelObjGL : public ModelObjGL
{
public:
	SimpleModelObjGL();
	SimpleModelObjGL(const std::string& model_file);
	~SimpleModelObjGL();

	void Init(const std::string& model_file);
};

#endif