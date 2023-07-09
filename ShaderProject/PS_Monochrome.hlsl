struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
}; 

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//ポストプロセスで画像に効果を加えるためにレンダーターゲットに書き込まれた色情報を取得
	color = tex.Sample(samp, pin.uv);

	//モノクロ
	float mono = 0.0f;
#if 0
	mono += color.r;
	mono += color.g;
	mono += color.b;
	mono /= 3.0f;
#else
	//人間の視覚特性を考慮したモノクロ
	//緑：変化を感じやすい
	//青：変化を感じにくい
	mono += color.r * 0.3f;
	mono += color.g * 0.6f;
	mono += color.b * 0.1f;
#endif

	color.rgb = mono;

	return color;
}