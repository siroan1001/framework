struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};
cbuffer Light : register(b0)
{
	float4 lightDiffuse;
	float4 lightAmbient;
	float4 lightDir;
};
//	ディゾルブのパラメータ
cbuffer Parameter : register(b1)
{
	float dissolveRate;		//	消す割合(0:全部表示/1:全部消す)
	float dissolveRange;	//	変化する範囲
	float2 dummy;			//	未使用
};
Texture2D tex : register(t0);
Texture2D dissolve : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color = tex.Sample(samp, pin.uv);

	//	パラメータ
	float3 N = normalize(pin.normal);
	float3 L = normalize(-lightDir.xyz);

	//	diffuse
	float diffuse = saturate(dot(N, L));
	color.rgb *= saturate(diffuse + lightAmbient);

	//	ディゾルブ
	float value = dissolve.Sample(samp, pin.uv).r;
#if 0	//	stepで二つに分けて表示(あんまり見た目は良くないかも...)
	color.a = step(dissolveRate, value);
#else
	//	変化範囲も考慮した全体の変化量
	float len = 1.0f + dissolveRange;
	//	変化範囲に併せて閾値を補正
	value += dissolveRange;
	//	基準値(rate)が0～1ではなく、
	//	0～(1+変化範囲)となるように変更
	float rate = dissolveRate * len;
	//	蒸気を踏まえて、0の時には全て不透明、
	//	1の時には全て透明となるように計算
	color.a = saturate(
		(value - rate) / dissolveRange
	);
#endif
	return color;
}