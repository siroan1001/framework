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

	//���m�N��
	float mono = 0.0f;
#if 0
	mono += color.r;
	mono += color.g;
	mono += color.b;
	mono /= 3.0f;
#else
	//�l�Ԃ̎��o�������l���������m�N��
	//�΁F�ω��������₷��
	//�F�ω��������ɂ���
	mono += color.r * 0.3f;
	mono += color.g * 0.6f;
	mono += color.b * 0.1f;
#endif

	color.rgb = mono;

	return color;
}