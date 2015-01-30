// �e�N�X�`���X�e�[�g
Texture2D		texDecal: register( t0 );		// �e�N�X�`��
SamplerState	samLinear : register( s0 );		// �T���v���[

// �O���[�o���ϐ��Q
cbuffer globalbuffer
{
	matrix world;		//	���[���h�s��
	matrix wvp;			//	�ϊ��s��
	float4 ambient;		//	�A���r�G���g(���g�p)
	float4 diffuse;		//	�f�B�t���[�Y
	float4 supecular;	//	�X�y�L����(���g�p)
	float4 light;		//	���C�g�x�N�g��
};

// �o�[�e�b�N�X�V�F�[�_�[�o�͍\����
struct VS_OUTPUT
{
	float4	pos		: SV_POSITION;
	float4	color	: NORMAL0;
	float2	uv		: TEXCOORD;
};

// �o�[�e�b�N�X�V�F�[�_�[
VS_OUTPUT FbxStaticShaderVS( float4 pos : POSITION, float4 norm : NORMAL, float2 uv : TEXCOORD )
{
	VS_OUTPUT output = ( VS_OUTPUT )0;

	// ���C�g�̃x�N�g���擾
	float3 lightDir = -light;

	// �@�������[���h�s��ŕϊ��Bx3�ɂ��Ă���͕̂��s�ړ��s����Ȃ�������
	// �@���A���C�g�x�N�g���̓��ώ擾�@normalize:���K��
	float3 normal	= normalize( mul( norm, ( float3x3 )world ) );
	lightDir = normalize( lightDir );

	// ���W�ϊ�
	output.pos		= mul( pos, wvp );

	// �@���A���C�g�x�N�g���̓��ώ擾�@normalize:���K��
	//normal = normalize( normal );
	//lightDir = normalize( lightDir );

	// dot:����

	// �@���ƃ��C�g�x�N�g���̓��ς��擾 saturate:臒l�O�`�P
	float4 NL = saturate( dot( normal, lightDir ) );
	NL.w = 1;

	// �f�B�t���[�Y�J���[�Ə�Z
	output.color = diffuse * NL;

	// �e�N�X�`���[���W�擾
	output.uv = uv;

	return output;
}

// �s�N�Z���V�F�[�_�[
float4 FbxStaticShaderPS( VS_OUTPUT input ) : SV_Target
{
	return texDecal.Sample( samLinear, input.uv );// * input.color;
}