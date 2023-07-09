struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	//	���[���h���W�̃f�[�^
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
	float4 camPos;	//	�J�����̃��[���h���W
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//	���̃x�N�g���Ɩ@������A���˂������(���˃x�N�g��)�����߂�
	//	�����̃x�N�g����@��������2�񓮂����ƁA���˃x�N�g���ɂȂ�!?
	float3 L = normalize(lightDir.xyz);
	float3 N = normalize(pin.normal.xyz);
//	float3 R = L + 2 * N * -dot(L, N);
	float3 R = reflect(L, N);

	//	���˒n�_(���[���h���W)����J�����Ɍ������x�N�g��
	float3 V = normalize(camPos.xyz - pin.worldPos.xyz);

	//	���˃x�N�g���ƁA�J�����Ɍ������x�N�g�������������Ȃ�
	//	�߂�����ῂ����Ȃ�͂�
	float specular = saturate(dot(R, V));
	//	�ݏ�̌v�Z���s���ƋǏ��I�ɖ��邭�Ȃ�
	//	������͈͂������Ȃ�
	specular = pow(specular, 20.0f);

	//	specular�����ł͖��邭�Ȃ邾���Ȃ̂ŁA
	//	�A������v�Z��������K�v������B
	float diffuse = saturate(dot(-L, N));


	color = tex.Sample(samp, pin.uv);
	color.rgb = color.rgb * 
		(diffuse + lightAmbient.rgb) + specular;

	return color;
}