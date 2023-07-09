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

	float2 center = float2(0.5f, 0.5f);
	float2 vec = pin.uv - center;
	float distance = length(vec);
	distance = pow(distance, 2.0f);
	distance *= 20.0f;

	float diff = distance / 1280.0f;
	color.r = tex.Sample(samp, pin.uv + float2(diff, 0.0f)).r;
	color.g = tex.Sample(samp, pin.uv - float2(diff, 0.0f)).g;

	return color;
}