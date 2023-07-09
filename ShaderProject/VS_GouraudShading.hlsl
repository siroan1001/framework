struct VS_IN{
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv :TEXCOORD0;
};

struct VS_OUT {
	float4 pos : SV_POSITION0;
	float4 color : COLOR0;	//	���_���Ōv�Z�������邳�̏��
	float2 uv : TEXCOORD0;
};

cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
}

//	���C�g�̏��
cbuffer Light : register(b1)
{
	float4 lightColor;
	float4 lightAmbient;
	float4 lightDir;
}

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);

	//	���_�V�F�[�_�[�ŉA�̌v�Z
	float3 N = vin.normal;
	float3 L = lightDir.xyz;
	//	�v�Z�O�Ɏ��������
	N = mul(N, (float3x3)world);
	L = -L;
	//	���K��
	N = normalize(N);
	L = normalize(L);
	//	�A�v�Z
	float diffuse = saturate(dot(N, L));
	//	�F����
	vout.color = float4(diffuse + lightAmbient.rgb, 1.0f);


	vout.uv = vin.uv;


	return vout;
}