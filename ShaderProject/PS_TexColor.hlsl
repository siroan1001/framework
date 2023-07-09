//	頂点シェーダから受け取るためのデータを定義
struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

//	テクスチャを受け取る
Texture2D tex : register(t0);
SamplerState samp : register(s0);	//	テクスチャの繰り返し設定

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);

	//	テクスチャからデータを取得
	color = tex.Sample(samp, pin.uv);

	return color;
}