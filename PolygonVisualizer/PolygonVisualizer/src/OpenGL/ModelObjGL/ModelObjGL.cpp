#include "./ModelObjGL.hpp"

ModelObjGL::ModelObjGL():
	material_id(0)
{
}

ModelObjGL::ModelObjGL(const std::string &model_file ,const std::string &material_file):
	material_id(0)
{
	/* objファイル読み込み */
	std::ifstream stream_model(model_file);
	ReadVertex(stream_model);
	/* mtlファイル読み込み */
	std::ifstream stream_material(material_file);
	ReadMaterial(stream_material);
}

ModelObjGL::~ModelObjGL()
{
}


void ModelObjGL::ReadVertex(std::ifstream &stream_model)
{
	if(stream_model.fail())
	{
		std::cerr << "ERROR: Cannot Open model file." << std::endl;
		std::abort();
	}

	int vline_start, vline_end;
	SearchStringLine(stream_model, "v ", &vline_start, &vline_end);
	std::vector<GLfloat> vert;
	GetVector(stream_model, vert,vline_start,vline_end);

	int vnline_start, vnline_end;
	SearchStringLine(stream_model, "vn ", &vnline_start, &vnline_end);
	std::vector<GLfloat> norm;
	GetVector(stream_model, norm, vnline_start, vnline_end);

	int fline_start, fline_end;
	SearchStringLine(stream_model, "f ", &fline_start, &fline_end);

	SetVertex(stream_model, vert, norm, fline_start, fline_end);
}

void ModelObjGL::SearchStringLine(std::ifstream &stream_model, const std::string &search_str, int *vstart, int *vend) const
{
	std::string buffer;
	int line_num = 1;

	stream_model.clear();
	stream_model.seekg(0, std::ios_base::beg);
	while(std::getline(stream_model, buffer))
	{
		if(buffer.find(search_str) != std::string::npos) break;
		line_num++;
	}
	*vstart = line_num;
	while(std::getline(stream_model, buffer))
	{
		if(buffer.find(search_str) == std::string::npos) break;
		line_num++;
	}
	*vend = line_num;
}

void ModelObjGL::GetVector(std::ifstream &stream_model,std::vector<GLfloat> &vec,const int &start,const int &end) const
{
	std::string buffer;

	/* ファイルシーク */
	stream_model.clear();
	stream_model.seekg(0,std::ios_base::beg);
	for(int i = 0;i < start-1;++i) std::getline(stream_model, buffer);

	/* ベクトル読み込み */
	for(int i = start-1;i < end;++i)
	{
		/* ヘッダ部分 */
		std::getline(stream_model, buffer, ' ');
		/* ベクトル(x,y,z) */
		std::getline(stream_model, buffer, ' ');
		vec.emplace_back(static_cast<GLfloat>(std::stod(buffer)));
		std::getline(stream_model, buffer, ' ');
		vec.emplace_back(static_cast<GLfloat>(std::stod(buffer)));
		std::getline(stream_model, buffer, '\n');
		vec.emplace_back(static_cast<GLfloat>(std::stod(buffer)));
	}
}

void ModelObjGL::SetVertex(std::ifstream &stream_model, const std::vector<GLfloat> &vert,const std::vector<GLfloat> &norm, const int &f_start,const int &f_end)
{
	std::string buffer;
	stream_model.clear();
	stream_model.seekg(0,std::ios_base::beg);
	for(int i = 0;i < f_start-1;++i) { std::getline(stream_model, buffer); }

	int v_index[3], n_index[3];
	for(int i = f_start-1;i < f_end;++i)
	{
		/* ヘッダ部分 */
		std::getline(stream_model, buffer, ' ');

		/* vertex1 */
		std::getline(stream_model, buffer, '/');
		v_index[0] = std::stoi(buffer) - 1;
		/* UV1(使用しない) */
		std::getline(stream_model, buffer, '/');
		/* 法線1 */
		std::getline(stream_model, buffer, ' ');
		n_index[0] = std::stoi(buffer) - 1;

		/* vertex2 */
		std::getline(stream_model, buffer, '/');
		v_index[1] = std::stoi(buffer) - 1;
		/* UV2(使用しない) */
		std::getline(stream_model, buffer, '/');
		/* 法線2 */
		std::getline(stream_model, buffer, ' ');
		n_index[1] = std::stoi(buffer) - 1;

		/* vertex3 */
		std::getline(stream_model, buffer, '/');
		v_index[2] = std::stoi(buffer) - 1;
		/* UV3(使用しない) */
		std::getline(stream_model, buffer, '/');
		/* 法線3 */
		std::getline(stream_model, buffer, '\n');
		n_index[2] = std::stoi(buffer) - 1;

		for(int j = 0;j < 3;++j)
		{
			m_vertex.emplace_back(ObjectGL::Vertex{vert[3*v_index[j]+0], vert[3*v_index[j]+1], vert[3*v_index[j]+2], norm[3*n_index[j]+0], norm[3*n_index[j]+1], norm[3*n_index[j]+2]});
		}
	}
}

void ModelObjGL::ReadMaterial(std::ifstream &stream_material)
{
	if(stream_material.fail())
	{
		std::cerr << "ERROR: Cannot Open material file." << std::endl;
		std::abort();
	}

	int start, end;
	SearchStringLine(stream_material, "Ka ", &start, &end);
	GetVector(stream_material, color, start, end);
	SearchStringLine(stream_material, "Kd ", &start, &end);
	GetVector(stream_material, color, start, end);
	SearchStringLine(stream_material, "Ks ", &start, &end);
	GetVector(stream_material, color, start, end);
	SearchStringLine(stream_material, "Kshi ", &start, &end);
	GetPoint(stream_material, color, start, end);
}

void ModelObjGL::GetPoint(std::ifstream &stream,std::vector<GLfloat> &vec,const int &start,const int &end) const
{
	std::string buffer;
	/* ファイルシーク */
	stream.clear();
	stream.seekg(0,std::ios_base::beg);
	for(int i = 0;i < start-1;++i) std::getline(stream, buffer);

	/* ベクトル読み込み */
	/* ヘッダ部分 */
	std::getline(stream, buffer, ' ');
	/* ベクトル(x) */
	std::getline(stream, buffer, '\n');
	vec.emplace_back(static_cast<GLfloat>(std::stod(buffer)));
}

void ModelObjGL::Set(const std::string &model_file,const std::string &material_file)
{
	/* objファイル読み込み */
	std::ifstream stream_model(model_file);
	ReadVertex(stream_model);
	/* mtlファイル読み込み */
	std::ifstream stream_material(material_file);
	ReadMaterial(stream_material);
}

void ModelObjGL::CpyColorToMaterial(MaterialGL &material)
{
	for(int i = 0;i < 3;++i) material.m_ambient[i]  = color[0+i];
	for(int i = 0;i < 3;++i) material.m_diffuse[i]  = color[3+i];
	for(int i = 0;i < 3;++i) material.m_specular[i] = color[6+i];
	material.m_shininess = color[9];
}
