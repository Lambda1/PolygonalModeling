#version 150 core
uniform mat4 model_view;
uniform mat4 projection;

in vec4 position;

void main()
{
	vec4 P = model_view * position; // 視点座標系の頂点位置

	gl_Position = projection * P;
}
