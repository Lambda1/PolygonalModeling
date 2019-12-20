#ifndef __MY_VIEWER_DEFINE_HPP__
#define __MY_VIEWER_DEFINE_HPP__

#include <string>

namespace MY_VIEWER_DEFINE
{
	namespace IMGUI
	{
		inline static const std::string GLSL_VERSION = "#version 150 core";
		inline static const char* GLSL_VERSION_C_STR = GLSL_VERSION.c_str();
	};
	namespace SHADER
	{
		inline static const std::string DIR = "../shader";
		inline static const std::string BASE_VERTEX   = DIR + "/base.vert";
		inline static const std::string BASE_FRAGMENT = DIR + "/base.frag";
	
		// シェーダ変数管理
		enum class TABLE : unsigned char
		{
			POSITION,
			NORMAL,
			MODEL_VIEW,
			PROJECION,
			NORMAL_MATRIX,
			LPOS,
			LAMB,
			LDIFF,
			LSPEC,
			MATERIAL,

			SIZE
		};
		inline static const std::string FRAGMENT = "fragment";
		inline static const std::string POSITION = "position";
		inline static const std::string NORMAL = "normal";
		inline static const std::string MODEL_VIEW = "model_view";
		inline static const std::string PROJECTION = "projection";
		inline static const std::string NORMAL_MATRIX = "normal_matrix";
		inline static const std::string MATERIAL = "Material";
		inline static const std::string LPOS = "Lpos";
		inline static const std::string LAMB = "Lamb";
		inline static const std::string LDIFF = "Ldiff";
		inline static const std::string LSPEC = "Lspec";
	};
	namespace STAGE_SHADER
	{
		inline static const std::string DIR = "../shader";
		inline static const std::string BASE_VERTEX = DIR + "/stage.vert";
		inline static const std::string BASE_FRAGMENT = DIR + "/stage.frag";

		// シェーダ変数管理
		enum class TABLE : unsigned char
		{
			POSITION,
			MODEL_VIEW,
			PROJECION,

			SIZE
		};
		inline static const std::string FRAGMENT = "fragment";
		inline static const std::string POSITION = "position";
		inline static const std::string MODEL_VIEW = "model_view";
		inline static const std::string PROJECTION = "projection";
	};
};

#endif