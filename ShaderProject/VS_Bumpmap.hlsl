struct VS_IN
{
    float3 pos : POSITION0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    // �ڃx�N�g���i�e�N�X�`���𒣂�t�����ۂ�
    float3 tangent : TANGENT0;
};
struct VS_OUT
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 lightAmbient : VECTOR0;
    // �ڃx�N�g����ԂɈړ����������C�g�̏��
    float3 lightT : NORMAL1;
    // �ڃx�N�g����ԂɈړ������������̏��
    float3 camVecT : NORMAL2;
};

cbuffer WVP : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};
cbuffer Light : register(b1) {
    float4 lightColor;
    float4 lightAmbient;
    float4 lightDir;
}
cbuffer Camera : register(b2) {
    float4 camPos;
}
//�o���v�}�b�v�ɂ��Ē��ׂ��̂ł����A�����炭�AVS_Bumpmap�̃e�N�X�`���̖@�������[���h��Ԃɕϊ����鏈����T, N, B�ł͂Ȃ�, T, B, N���Ǝv���܂�

VS_OUT main(VS_IN vin)
{
    VS_OUT vout;

    vout.pos = float4(vin.pos, 1.0f);
    vout.pos = mul(vout.pos, world);
    float4 worldPos = vout.pos; // �v�Z�r���Ń��[���h���W�̏���ϐ��ɃR�s�[
    vout.pos = mul(vout.pos, view);
    vout.pos = mul(vout.pos, proj);

    vout.uv = vin.uv;

    vout.normal = mul(vin.normal, (float3x3)world);

    // �ڃx�N�g���Ɩʖ@������]�@��(Binormal)���v�Z
    float3 T = mul(vin.tangent, (float3x3)world);
    T = normalize(T);
    float3 N = normalize(vout.normal);
    float3 B = normalize(cross(T, N));
    // 3�̃x�N�g������A�e�N�X�`���̖@�������[���h��Ԃɕϊ����邽�߂̍s��
    float3x3 tangentMat = float3x3(T, B, N);

    // �@���Ƃ̌v�Z���s�������̃x�N�g�����A���[���h��Ԃ���e�N�X�`����Ԃֈړ�������
    // ���ڃx�N�g���̕ϊ��s��̋t�s������߂�΂悢
    tangentMat = transpose(tangentMat);
    float3 invLightDir = normalize(lightDir.xyz);
    invLightDir = mul(invLightDir, tangentMat);
    vout.lightT = invLightDir;

    vout.lightAmbient = lightAmbient;

    // �����x�N�g�������[���h��Ԃ���e�N�X�`����Ԃֈړ�������
    float4 camVec = worldPos - camPos;
    vout.camVecT = mul(camVec.xyz, tangentMat);

    return vout;
}