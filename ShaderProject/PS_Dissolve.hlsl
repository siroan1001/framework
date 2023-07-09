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
//	�f�B�]���u�̃p�����[�^
cbuffer Parameter : register(b1)
{
	float dissolveRate;		//	��������(0:�S���\��/1:�S������)
	float dissolveRange;	//	�ω�����͈�
	float2 dummy;			//	���g�p
};
Texture2D tex : register(t0);
Texture2D dissolve : register(t1);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	color = tex.Sample(samp, pin.uv);

	//	�p�����[�^
	float3 N = normalize(pin.normal);
	float3 L = normalize(-lightDir.xyz);

	//	diffuse
	float diffuse = saturate(dot(N, L));
	color.rgb *= saturate(diffuse + lightAmbient);

	//	�f�B�]���u
	float value = dissolve.Sample(samp, pin.uv).r;
#if 0	//	step�œ�ɕ����ĕ\��(����܂茩���ڂ͗ǂ��Ȃ�����...)
	color.a = step(dissolveRate, value);
#else
	//	�ω��͈͂��l�������S�̂̕ω���
	float len = 1.0f + dissolveRange;
	//	�ω��͈͂ɕ�����臒l��␳
	value += dissolveRange;
	//	��l(rate)��0�`1�ł͂Ȃ��A
	//	0�`(1+�ω��͈�)�ƂȂ�悤�ɕύX
	float rate = dissolveRate * len;
	//	���C�𓥂܂��āA0�̎��ɂ͑S�ĕs�����A
	//	1�̎��ɂ͑S�ē����ƂȂ�悤�Ɍv�Z
	color.a = saturate(
		(value - rate) / dissolveRange
	);
#endif
	return color;
}