#version 150 core
uniform mat4 model_view;
uniform mat4 projection;
uniform mat3 normal_matrix;

in vec4 position;
in vec3 normal;

out vec4 P; // 視点位置
out vec3 N; // 法線ベクトル

void main()
{
	P = model_view * position; // 視点座標系の頂点位置
	N = normalize(normal_matrix * normal); // 法線ベクトルの補正

	gl_Position = projection * P;
}
