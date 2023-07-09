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
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	
	//�𑜓x�������ăh�b�g�G�̂悤�ȕ\��
	//UV�̃T�C�Y���グ�āA���������؂�̂�
	float2 dotScreenSize = float2(16.0f, 9.0f);
	float rate = 10.0f;
	dotScreenSize *= rate;
	float2 i_uv = pin.uv * dotScreenSize;
	i_uv = floor(i_uv);	//�����̐؂�̂�

	//�傫���Ȃ��Ă���UV�̑傫�������ɖ߂�
	//�����������͐؂�̂ĂĂ�̂Ńu���b�N���Ƃ�UV�w��ɂȂ�
	i_uv /= dotScreenSize;

	//�u���b�N���ƂɂȂ���UV�l�Ńe�N�X�`���̐F�擾
	color = tex.Sample(samp, i_uv);
	return color;
}