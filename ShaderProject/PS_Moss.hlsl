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
Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	color = tex.Sample(samp, pin.uv);

	//	@ό
	float3 N = normalize(pin.normal);
	//	ΫͺΆ¦ιorαͺΟΰιϋό
	float3 MossDir = float3(0, 1, 0);
	MossDir = normalize(MossDir);

	//	ΫΜΆ¦ο
	float moss = dot(N, MossDir);
	float mossStart = 0.5f;	//	Ο»΅nί
	float mossRange = 0.1f;	//	Ο»ΝΝ
	moss = moss - mossStart;	
	moss = moss / mossRange;
	moss = saturate(moss);	//	0`1Ιϋίι
	moss *= 0.75f;

	//	ΫπΆβ·
	float3 mossColor = float3(0.0f, 0.8f, 0.2f);
	color.rgb = lerp(color.rgb, mossColor, moss);



	return color;
}