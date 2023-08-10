//	���_�V�F�[�_����󂯎�邽�߂̃f�[�^���`
struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
};

//	�e�N�X�`�����󂯎��
Texture2D tex : register(t0);
SamplerState samp : register(s0);	//�e�N�X�`���̌J��Ԃ��ݒ�

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(1.0f, 1.0f, 1.0f, 1.0f);
	//	�e�N�X�`������f�[�^���擾
	color = tex.Sample(samp, pin.uv);
	
	return color;
}