struct PS_IN{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : POSITION0;
};
cbuffer Light : register(b0){
	float4 lightColor;
	float4 lightAmbient;
	float4 lightDir;
};
cbuffer Camera : register(b1){
	float4 camPos;	//	�J�����̃��[���h���W
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//	�@�t�����ǂ����v�Z
	float3 L = normalize(lightDir.xyz);
	float3 V = normalize(camPos.xyz - pin.worldPos.xyz);
	float backLight = saturate(dot(L, V));

	//	�A��(�@���ɑ΂��Ď����������ɓ�����ӏ�)�̌v�Z
	float3 N = normalize(pin.normal);
	float edge = dot(N, V);
	edge = 1.0f - abs(edge);	//	�����ȕ��������邭�Ȃ�悤�Ɍv�Z���ʂ��Ђ�����Ԃ�
	edge = pow(edge, 5.0f);	//	�Ε����݂̂�����

	//	�������C�g�̌v�Z
	float rim = backLight * edge;

	//	�e�N�X�`���\��t���Ċg�U���v�Z
	float diffuse = saturate(dot(N, -L));
	color = tex.Sample(samp, pin.uv);


	color.rgb = color.rgb * (diffuse + lightAmbient.rgb) + rim;

	return color;
}