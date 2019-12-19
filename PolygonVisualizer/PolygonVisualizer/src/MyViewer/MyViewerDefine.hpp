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
	};
};

#endif