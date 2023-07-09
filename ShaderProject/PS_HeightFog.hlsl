struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : POSITION0;
};
cbuffer Light : register(b0) {
	float4 lightColor;
	float4 lightAmbient;
	float4 lightDir;
};
cbuffer Camera : register(b1) {
	float4 camPos;
};
//	フォグの設定
cbuffer FogParam : register(b2) {
	float4 fogColor;	//	フォグの色
	float2 distanceFog;	//	距離のフォグの情報(未使用)
	float fogStart;	//	フォグの開始高さ
	float fogRange;	//	フォグの範囲
}

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//	フォグの色を計算する地点までの距離
	float height = pin.worldPos.y;

	//	フォグの色を変化させる係数の計算
	float fog = 0.0f;
	fog = height - fogStart;	//	フォグの開始距離で引く
	fog = fog / fogRange;	//	フォグの適用範囲で割る
	fog = saturate(-fog);	//	マイナスをかけてから、0～1で丸め込む

	//	元の色
	float3 N = normalize(pin.normal);
	float3 L = normalize(lightDir.xyz);
	float diffuse = saturate(dot(N, -L));
	color = tex.Sample(samp, pin.uv);
	color.rgb = color.rgb * (diffuse + lightAmbient.rgb);

	//	係数から元の色とフォグの色を変化させる
	color.rgb = lerp(color.rgb, fogColor.rgb, fog);

	return color;
}