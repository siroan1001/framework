//	2D�̔|���S���Ȃ̂ŁA3D�Ƃ͕ʂ̃f�[�^���n�����
struct PS_IN{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer Parameter : register(b0)
{
	float innerDistance;	//	�����̉��̋���
	float outerDistance;	//	�O���̗΂̋���
	float gageRate;			//	�Q�[�W�̌��ݗ�
	float dummy;			//	���g�p
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//	UV�̒l����A���S�܂ł̋��������߂�
	float2 center = float2(0.5f, 0.5f);
	float2 offset = pin.uv - center;
	float r = length(offset);

	//	���S����̋�������\�����邩���Ȃ�������
	//	������if�����g���ƑS�Ẵs�N�Z���Ōv�Z���邱�ƂɂȂ�̂ŁA
	//	if�����g�킸�ɕ\���̔���(�v�Z)���s��
	//	step ... ���̐��l(�萔)���A�E�̐��l���傫�����
	//	1,�����łȂ����0��Ԃ�
	float inner = 1.0f -  step(innerDistance, r);
	float outer = step(outerDistance, r);
	color.a = inner * outer;


	//	�ɍ��W�̊p�x�����߂�
	float pi = 3.141592f;
	float rad = atan2(offset.y, offset.x);	//	���W����p�x���v�Z
	rad -= pi * 0.5f;			//	�p�x��ς��ăQ�[�W�̃X�^�[�g�n�_��ύX
	rad /= pi;					//	-3.14�`3.14��-1�`1�ɕϊ�
	rad = rad * 0.5f + 0.5f;	//	-1�`1��0�`1�ɕϊ�
	rad = frac(rad);	//	�Q�[�W�̃X�^�[�g�n�_�̕ύX��0.25�`1.25�ɂȂ��Ă�
						//	�̂ŁAfrac�֐��ŏ����������������o���B
	float gage = rad;
	gage = 1.0f - step(gageRate, gage);
	float3 frontColor = float3(0.0f, 1.0f, 0.3f);
	float3 backColor = float3(0.3f, 0.3f, 0.3f);

	//	UV���W�ɋɍ��W��(�p�x�A����)��ݒ肷��ƁA
	//	�������΂���ăe�N�X�`�����\��t������B
	frontColor = tex.Sample(samp, float2(rad, r * 2.0f));

	color.rgb = lerp(backColor, frontColor, gage);


	return color;
}