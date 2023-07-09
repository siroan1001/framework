struct PS_IN
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 lightAmbient : VECTOR0;
    float3 lightT : NORMAL1;
    float3 camVecT : NORMAL2;
};
SamplerState samp : register(s0);
Texture2D tex : register(t0);
Texture2D normalMap : register(t1);
Texture2D heightMap : register(t2);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

    // ----- �����Օ��}�b�s���O
    // �|���S���ʂ��王�������ɉ�����Ȃ���A�n�C�g�}�b�v�̍����Ƌt�]����ꏊ��T��
    // �������t�]����ʒu��T�����߂̃��[�v��
    int nStep = 100;
    float maxHeight = 0.05f;
    float stepHeight = maxHeight / nStep;

    // �ڃx�N�g�����UV���W�̈ړ��ʂ��v�Z(1step������̍����̕ω��ʂɂ��낦��)
    float3 offset = pin.camVecT;
    offset.xy *= stepHeight / offset.z;
    offset.z = stepHeight;

    // 1���[�v�Ői�ޗʂ����܂����̂ŁA�n�C�g�}�b�v�̍����Ƌt�]����ʒu�܂Ői��
    float2 uv = pin.uv;
    float eyeHeight = maxHeight;
    // unroll...���[�v�̍ő�񐔂�ݒ肷��
    [unroll(100)]for (int i = 0; i < nStep; ++i) {
        float height = heightMap.Sample(samp, uv).r;
        height *= maxHeight;
        if (height >= eyeHeight) {
            break;
        }
        // ���_�̍����AUV���ړ�������
        uv -= offset.xy;
        eyeHeight -= offset.z;
    }

    // �@���}�b�v����@���̃f�[�^���擾
    float3 N = normalMap.Sample(samp, uv).rgb;
    N = normalize(N * 2.0f - 1.0f);
    // ���O�Ɍv�Z���ꂽ�e�N�X�`����Ԃ̃��C�g
    float3 L = normalize(pin.lightT);

    // �@���ƃ��C�g���疾�邳���v�Z(���܂Œʂ�)
    float diffuse = saturate(dot(-L, N));
    color = tex.Sample(samp, uv);
    color.rgb = color.rgb * (diffuse + pin.lightAmbient.rgb);

    return color;
}