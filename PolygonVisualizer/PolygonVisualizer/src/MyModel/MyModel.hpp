#ifndef __MY_MODEL_HPP__
#define __MY_MODEL_HPP__

#include "../OpenGL/ObjectGL/ObjectGL.hpp"
#include "../OpenGL/PrimitiveObjectGL/CubeGL.hpp"

#include <GL/glew.h>

#include <algorithm>
#include <string>
#include <vector>

class MyModel
{
	// 定数パラメータ
	inline static const std::string DEFAULT_STRING = "NONE";

	// 基本モデルデータ
	std::string m_file_name;         // ファイルネーム
	std::string m_file_extension;    // 拡張子
	int m_vertex_count, m_face_count; // 頂点・ポリゴン数
	bool is_registration;            // 図形が登録されているか
	// 頂点・法線データ
	std::vector<ObjectGL::Vertex> m_model;
	// インデックスデータ
	std::vector<GLuint> m_index_data;

	// ファイル情報を登録
	void RegistrationFileIndo(const std::string &file_path);

public:
	MyModel();
	~MyModel();

	// モデルデータ読み込み
	void LoadModelData(const std::string &open_model_data);
	// モデルが登録されているか
	inline bool IsRegistration() const { return is_registration; }

	// Getter
	// モデルデータ
	inline const ObjectGL::Vertex* GetModelData() const { return m_model.data(); }
	inline int GetModelDataSize() const { return static_cast<int>(m_model.size()); }
	inline const GLuint* GetIndexData() const { return m_index_data.data(); }
	inline int GetIndexDataSize() const { return static_cast<int>(m_index_data.size()); }
	// モデルヘッダ
	inline std::string GetFileName() const { return m_file_name; }
	inline const char* GetFileName_C_STR() const { return m_file_name.c_str(); }
};

#endif