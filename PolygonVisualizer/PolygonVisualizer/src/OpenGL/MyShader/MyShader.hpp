#ifndef __MY_SHADER_HPP__
#define __MY_SHADER_HPP__
// ri-ku
#include <iostream>
#include <string>
#include <fstream>

#include <GL/glew.h>

class MyShader{
	GLint compiled, linked;
	/* Vertex-shader and Fragment-shader: variable */
	GLuint vertShader, fragShader;
	GLuint gl2Program;

	bool VCompile(std::string&);
	bool FCompile(std::string&);
	bool Link();
	
	void PrintCompileError(const GLuint);
	
	public:
	MyShader() :
	compiled(0), linked(0),
	vertShader(0), fragShader(0),
	gl2Program(0)
	{}
	MyShader(const std::string, const std::string);
	~MyShader();
	bool Set(const std::string, const std::string);
	void UseProgram();
	void UnUseProgram();
	
	/* vec1型 */
	/* uniform変数の場所, 設定する値 */
	inline void Uniform1i(const GLint &location,const GLint &v0){ glUniform1i(location, v0); }
	inline void Uniform1f(const GLint &location,const GLfloat &v0){ glUniform1f(location, v0); }
	/* vec2型 */
	/* uniform変数の場所, uniformの要素数(配列でなければ1), 設定する値の配列(count*2以上必要) */
	inline void Uniform2fv(const GLint &location,const GLsizei &count,const GLfloat *value){ glUniform2fv(location, count, value); }
	/* vec3型 */
	inline void Uniform3fv(const GLint &location, const GLsizei &count, const GLfloat *value){ glUniform3fv(location, count, value); }
	/* vec4型 */
	inline void Uniform4fv(const GLint &location, const GLsizei &count, const GLfloat *value){ glUniform4fv(location, count, value); }
	/* matrix型 */
	/* uniform変数の場所, mat4の要素数(配列でなければ1), 配列の転置を行うか, 4*4行列(count*16個) */
	inline void UniformMatrix4fv(const GLint &location, const GLsizei &count,const GLboolean &transpose, const GLfloat *value){ glUniformMatrix4fv(location, count, transpose, value); }
	inline void UniformMatrix3fv(const GLint &location, const GLsizei &count,const GLboolean &transpose, const GLfloat *value){ glUniformMatrix3fv(location, count, transpose, value); }
	/* UBO */
	inline void UniformBlockBind(const GLuint &index, const GLuint &bind_num){glUniformBlockBinding(gl2Program, index, bind_num);  }

	/* Setter */
	inline void BindFragDataLocation(const std::string &str){ glBindFragDataLocation(gl2Program, 0, str.c_str());  }

	/* Getter */
	inline GLuint GetProgramID(){ return gl2Program; }
	inline GLint GetAttLocationValue(const std::string var){ return glGetAttribLocation(gl2Program, var.c_str()); }
	inline GLint GetUniLocationValue(const std::string var){ return glGetUniformLocation(gl2Program, var.c_str()); }
	inline GLint GetUniformBlockIndex(const std::string var){ return glGetUniformBlockIndex(gl2Program, var.c_str()); }
};

#endif
