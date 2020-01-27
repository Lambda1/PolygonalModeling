#version 150 core

// 光源データ
const int Lcount = 1; // 光源数
uniform vec4 Lpos[Lcount];  // 光源の同次座標
uniform vec3 Lamb[Lcount];  // 環境光強度
uniform vec3 Ldiff[Lcount]; // 光源強度の拡散反射光成分
uniform vec3 Lspec[Lcount]; // 鏡面反射光成分

in vec4 P;
in vec3 N;
in vec3 vColor;

out vec4 fragment;

void main()
{
	vec3 V = -normalize(P.xyz); // 視点方向ベクトル

	vec3 Ispec = vec3(0.0); // 拡散反射光強度
	vec3 Idiff = vec3(0.0); // 鏡面反射光強度
	for(int i = 0;i < Lcount;++i)
	{
		vec3 L = normalize((Lpos[i]*P.w - P*Lpos[i].w).xyz); // 光源方向ベクトル
		vec3 Iamb = Lamb[i]; // 環境光の反射強度
		Idiff += max(dot(N, L), 0.0) * Ldiff[i] + Iamb;  // 拡散反射光強度
		vec3 H = normalize(L+V); // 中間ベクトル
		Ispec += pow(max(dot(normalize(N),H),0.0),1.0) * Lspec[i];
	}

	fragment = vec4(vColor*Idiff + Ispec, 1.0); // アルファ値:1.0
}
