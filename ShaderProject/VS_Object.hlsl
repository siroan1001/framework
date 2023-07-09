//	�C���v�b�g���C�A�E�g
//	CPU����n����钸�_�̏����`��������
struct VS_IN
{
	float3 pos : POSITION0;		//	�Z�}���e�B�N�X
	float3 normal : NORMAL0;	//	�f�[�^�̗p�r���`����
	float2 uv : TEXCOORD0;
};

//	���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�֑���f�[�^�̒�`
struct VS_OUT
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};

//	�萔�o�b�t�@
//	CPU��GPU�ł���肷��A���_�ȊO�̃f�[�^���i�[�����
cbuffer WVP: register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	//	���[�J�����W���X�N���[�����W�֕ϊ�
	vout.pos = float4(vin.pos, 1.0f);	//	���[�J�����W
	vout.pos = mul(vout.pos, world);	//	���[���h���W
	vout.pos = mul(vout.pos, view);		//	�r���[���W
	vout.pos = mul(vout.pos, proj);		//	�v���W�F�N�V�������W

	//	�s�N�Z���V�F�[�_�[�ŗ��p����UV���W��n��
	vout.uv = vin.uv;

	//	�s�N�Z���V�F�[�_�[�ŗ��p����@����n��
	//	�@���̓I�u�W�F�N�g�̉�]�ɕ����ĉ�]�����Ȃ��Ƃ������Ȍ����ڂɂȂ�B
	//	���[���h�s��ɂ͈ړ��������܂܂�邪�A�ړ���@���ɓK�p���Ă���������
	//	�Ȃ�̂ŁA��]�����݂̂̍s��ƂȂ�悤�ɏk�����Čv�Z����B
	vout.normal = mul(vin.normal,(float3x3)world);

	return vout;
}