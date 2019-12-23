#ifndef __MY_MODEL_HPP__
#define __MY_MODEL_HPP__

#include "../OpenGL/ObjectGL/ObjectGL.hpp"
#include "../ModelReader/PCDReader/PCDReader.hpp"
#include "../ModelReader/Bin4Reader/Bin4Reader.hpp"
#include "../OpenGL/MatrixGL/MatrixGL.hpp"
#include "../OpenGL/MathGL/MathGL.hpp"
#include "../OpenGL/PrimitiveObjectGL/CubeGL.hpp"

#include <GL/glew.h>

#include <algorithm>
#include <string>
#include <vector>

class MyModel
{
public:
	enum class MODEL_TYPE
	{
		NONE,
		PARTICLE,
		PARTICLE_COLOR,
		WIRE,
		POLYGON
	};
	// 拡張子
	inline static const std::string EXTENSION_PCD = ".pcd";
	inline static const std::string EXTENSION_BIN4 = ".bin4";
private:
	// 定数パラメータ
	inline static const std::string DEFAULT_STRING = "NONE";

	// モデルデータ
	ModelReader* m_model_data;
	// 基本モデルデータ
	std::string m_file_name;         // ファイルネーム
	std::string m_file_extension;    // 拡張子
	int m_vertex_count, m_face_count; // 頂点・ポリゴン数
	bool is_registration;            // 図形が登録されているか
	MODEL_TYPE m_model_type;
	// 頂点・法線データ
	std::vector<ObjectGL::Vertex> m_model;
	// インデックスデータ
	std::vector<GLuint> m_index_data;
	// モデル行列
	MatrixGL m_model_matrix;
	MatrixGL m_translate, m_scale; // 平行移動, スケール
	GLfloat m_angle_rad;

	// ファイル情報を登録
	void RegistrationFileIndo(const std::string &file_path);
	// データ整形
	void SetVertexParticle(); // 粒子のみ
	void SetVertexParticleColor(); // 点群+色
public:
	MyModel();
	~MyModel();

	// モデルデータ読み込み
	void LoadModelData(const std::string &open_model_data);
	// モデルが登録されているか
	inline bool IsRegistration() const { return is_registration; }

	// モデル行列の計算
	inline void CalcModelMatrix(const MatrixGL& view)
	{
		m_model_matrix = view * m_translate * m_scale;
	}

	// Setter
	inline void SetTranslateMatrix(const GLfloat& x, const GLfloat& y, const GLfloat& z) { m_translate = MathGL::Translate(x,y,z); }
	inline void SetFixedScaleMatrix(const GLfloat& scale) { m_scale = MathGL::Scale(scale, scale, scale); }

	// Getter
	// モデルデータ
	inline const ObjectGL::Vertex* GetModelData() const { return m_model.data(); }
	inline int GetModelDataSize() const { return static_cast<int>(m_model.size()); }
	inline const GLuint* GetIndexData() const { return m_index_data.data(); }
	inline int GetIndexDataSize() const { return static_cast<int>(m_index_data.size()); }
	inline MODEL_TYPE GetModelType() const { return m_model_type; }
	// モデルヘッダ
	inline std::string GetFileName() const { return m_file_name; }
	inline const char* GetFileName_C_STR() const { return m_file_name.c_str(); }
	inline int GetModelFaceNum() const { return m_face_count; }
	inline int GetModelVertexNum() const { return m_vertex_count; }
	// モデル姿勢
	inline const MatrixGL& GetModelMatrix() const { return m_model_matrix; }
	inline const GLfloat* GetModelMatrixPtr() const { return m_model_matrix.GetMatrix(); }
	inline void GetModelNormal(GLfloat* normal) const { m_model_matrix.GetNormalMatrix(normal); }
};

#endif