#include "./MyShader.hpp"

MyShader::MyShader(const std::string fname1, const std::string fname2) :
	compiled(0), linked(0),
	vertShader(0), fragShader(0),
	gl2Program(0)
{
	std::ifstream ifs_v(fname1),ifs_f(fname2);

	std::string source1((std::istreambuf_iterator<char>(ifs_v)),std::istreambuf_iterator<char>());
	std::string source2((std::istreambuf_iterator<char>(ifs_f)),std::istreambuf_iterator<char>());

	source1.push_back('\0');
	source2.push_back('\0');
	VCompile(source1);
	FCompile(source2);
	Link();

	glUseProgram(gl2Program);
	ifs_v.close();
	ifs_f.close();
}

MyShader::~MyShader()
{
	glUseProgram(0);
	glDeleteShader(compiled);
	glDeleteShader(linked);
	glDeleteProgram(gl2Program);
}

bool MyShader::Set(const std::string fname1,const std::string fname2)
{
	std::ifstream ifs_v(fname1),ifs_f(fname2);

	std::string source1((std::istreambuf_iterator<char>(ifs_v)),std::istreambuf_iterator<char>());
	std::string source2((std::istreambuf_iterator<char>(ifs_f)),std::istreambuf_iterator<char>());

	source1.push_back('\0');
	source2.push_back('\0');
	if(!VCompile(source1)){ exit(EXIT_FAILURE); }
	if(!FCompile(source2)){ exit(EXIT_FAILURE); }
	Link();

	glUseProgram(gl2Program);

	ifs_v.close();
	ifs_f.close();

	return true;
}

bool MyShader::VCompile(std::string &source)
{
	const GLchar *s_ptr = reinterpret_cast<const GLchar *>(source.c_str());
	GLint s_length = static_cast<GLint>(source.length());

	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader,1,&s_ptr,&s_length);

	/* Compile: Vertex-Shader */
	glCompileShader(vertShader);
	glGetShaderiv(vertShader,GL_COMPILE_STATUS,&compiled);

	/* Compile Error Message */
	if (compiled == GL_FALSE) {
		PrintCompileError(vertShader);
		std::cout << "COMPILE ERROR: VERTEX PROGRAM" << std::endl;
		return false;
	}
	return true;
}

bool MyShader::FCompile(std::string &source)
{
	const GLchar *s_ptr = reinterpret_cast<const GLchar *>(source.c_str());
	const GLint s_length = static_cast<GLint>(source.length());

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader,1,&s_ptr,&s_length);

	/* Compile: Fragment-Shader */
	glCompileShader(fragShader);
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &compiled);

	/* Compile Error Message */
	if (compiled == GL_FALSE) {
		PrintCompileError(fragShader);
		std::cout << "COMPILE ERROR: FRAGMENT PROGRAM" << std::endl;
		return false;
	}
	return true;
}

bool MyShader::Link()
{
	gl2Program = glCreateProgram();
	/* Registration: Shader */
	glAttachShader(gl2Program, vertShader);
	glDeleteShader(vertShader);
	glAttachShader(gl2Program, fragShader);
	glDeleteShader(fragShader);
	/* Link: Shader */
	glLinkProgram(gl2Program);
	glGetProgramiv(gl2Program, GL_LINK_STATUS, &linked);
	if (linked == GL_FALSE)
	{
		std::cout << "LINK ERROR: LINK" << std::endl;
		return false;
	}
	return true;
}

void MyShader::PrintCompileError(const GLuint m_shader)
{
	GLsizei size;
	glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &size);

	GLchar *buf = new GLchar[size];
	GLsizei len;
	glGetShaderInfoLog(m_shader, size, &len, buf);
	std::cerr << buf << std::endl;
	
	delete[] buf;
}

void MyShader::UseProgram()
{
	glUseProgram(gl2Program);
}

void MyShader::UnUseProgram()
{
	glUseProgram(0);
}
