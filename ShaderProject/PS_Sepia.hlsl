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

	//モノクロに変換
	color.rgb = color.rgb * 0.3f + color.g * 0.6f + color.b * 0.1f;

	//緑と青の成分を下げて全体を赤みがかった画像とする
	color.g *= 0.7f;
	color.b *= 0.4f;

	return color;
}