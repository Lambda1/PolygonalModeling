#ifndef _MODEL_OBJ_GL_HPP__
#define _MODEL_OBJ_GL_HPP__

#include "../ObjectGL/ObjectGL.hpp"
#include "../MaterialGL/MaterialGL.hpp"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class ModelObjGL
{
protected:
	std::vector<ObjectGL::Vertex> m_vertex; /* 頂点(3)+法線(3) */
	
	GLuint material_id;     /* シェーダ用ID */
	std::vector<GLfloat> color; /* Ambi, Diff, Spec, Kshi */

	/* モデルデータ読み込み */
	void ReadVertex(std::ifstream &stream_model);
	/* ファイル中のstrの位置を検索 */
	void SearchStringLine(std::ifstream &stream_model,const std::string &search_str, int *vstart, int *vend) const;
	/* start-end間の3次元ベクトルをvecに読み込む */
	void GetVector(std::ifstream &stream_model,std::vector<GLfloat> &vec,const int &start,const int &end) const;
	/* 頂点+法線データをm_vertexにセット */
	void SetVertex(std::ifstream &stream_model, const std::vector<GLfloat> &vert,const std::vector<GLfloat> &norm, const int &f_start,const int &f_end);
	
	/* マテリアルデータ読み込み */
	void ReadMaterial(std::ifstream &stream_material);
	/* start-end間の1次元ベクトルをvecに読み込む */
	void GetPoint(std::ifstream &stream_model,std::vector<GLfloat> &vec,const int &start,const int &end) const;

public:
		ModelObjGL();
		ModelObjGL(const std::string &model_file,const std::string &material_file);
		virtual ~ModelObjGL();

	void Set(const std::string &model_file,const std::string &material_file);

	/* Materialのコピー */
	void CpyColorToMaterial(MaterialGL &material);
	
	/* Getter */
	inline const ObjectGL::Vertex *GetVertex() const { return m_vertex.data(); }
	inline const int GetVertexSize() const { return static_cast<int>(m_vertex.size()); }
	virtual inline const GLfloat *GetMaterial() const { return color.data(); }
	inline const GLuint GetMaterialID() const { return material_id; }

	/* Setter */
	inline void SetMaterialID(const GLuint &id) { material_id = id; }
};

#endif