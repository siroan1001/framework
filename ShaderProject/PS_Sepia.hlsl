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

	//�|�X�g�v���Z�X�ŉ摜�Ɍ��ʂ������邽�߂Ƀ����_�[�^�[�Q�b�g�ɏ������܂ꂽ�F�����擾
	color = tex.Sample(samp, pin.uv);

	//���m�N���ɕϊ�
	color.rgb = color.rgb * 0.3f + color.g * 0.6f + color.b * 0.1f;

	//�΂Ɛ̐����������đS�̂�Ԃ݂��������摜�Ƃ���
	color.g *= 0.7f;
	color.b *= 0.4f;

	return color;
}