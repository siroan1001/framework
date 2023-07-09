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
	color = tex.Sample(samp, pin.uv);

	float4 frame = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float2 uv = pin.uv;
	//���̓I�Ɍ�����e�̌v�Z
	//�̈���^�i�ȂȂ߁j�ŋ�؂��Ė��邢�����ƈÂ��������v�Z
	frame.rgb = step(uv.x + uv.y, 1.0f) * 0.7f;
	//�̈���t�^�ŋ�؂��āA��قǂ̖��邳�̌��ʂƍ�������
	frame.rgb += step(uv.y, uv.x) * 0.3f;

	//���ɓ����镔�����P�C����ȊO���O�ɂȂ�悤�Ɍv�Z
	//���S���O�C�O�Ƃ������W�ōl����
	uv = uv - float2(0.5f, 0.5f);
	uv = abs(uv);
	float mask = step(0.3f, max(uv.x, uv.y));
	
	//���O�Ɍv�Z�����p�����[�^�𗘗p���āA�����\��
	color = lerp(color, frame, mask);

	return color;
}