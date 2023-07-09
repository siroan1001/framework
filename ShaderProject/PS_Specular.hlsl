struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	//	ワールド座標のデータ
	float4 worldPos : POSITION0;
}; 

cbuffer Light : register(b0)
{
	float4 lightColor;
	float4 lightAmbient;
	float4 lightDir;
};

cbuffer Camera : register(b1)
{
	float4 camPos;	//	カメラのワールド座標
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//	光のベクトルと法線から、反射する方向(反射ベクトル)を求める
	//	※光のベクトルを法線方向に2回動かすと、反射ベクトルになる!?
	float3 L = normalize(lightDir.xyz);
	float3 N = normalize(pin.normal.xyz);
//	float3 R = L + 2 * N * -dot(L, N);
	float3 R = reflect(L, N);

	//	反射地点(ワールド座標)からカメラに向かうベクトル
	float3 V = normalize(camPos.xyz - pin.worldPos.xyz);

	//	反射ベクトルと、カメラに向かうベクトルが同じ方向なら
	//	めっちゃ眩しくなるはず
	float specular = saturate(dot(R, V));
	//	累乗の計算を行うと局所的に明るくなる
	//	※光る範囲が狭くなる
	specular = pow(specular, 20.0f);

	//	specularだけでは明るくなるだけなので、
	//	陰をつける計算も加える必要がある。
	float diffuse = saturate(dot(-L, N));


	color = tex.Sample(samp, pin.uv);
	color.rgb = color.rgb * 
		(diffuse + lightAmbient.rgb) + specular;

	return color;
}