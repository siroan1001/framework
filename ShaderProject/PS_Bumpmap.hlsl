struct PS_IN
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 lightAmbient : VECTOR0;
    // �ڃx�N�g����ԂɈړ����������C�g�̏��
    float3 lightT : NORMAL1;
};
SamplerState samp : register(s0);
Texture2D tex : register(t0);
Texture2D normalMap : register(t1);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

    // �@���}�b�v����@���̃f�[�^���擾
    float3 N = normalMap.Sample(samp, pin.uv);
    N = normalize(N * 2.0f - 1.0f);
    // ���O�Ɍv�Z���ꂽ�e�N�X�`����Ԃ̃��C�g
    float3 L = normalize(pin.lightT);

    // �@���ƃ��C�g���疾�邳���v�Z(���܂Œʂ�)
    float diffuse = saturate(dot(-L, N));
    color = tex.Sample(samp, pin.uv);
    color.rgb = color.rgb * (diffuse + pin.lightAmbient.rgb);


	return color;
}