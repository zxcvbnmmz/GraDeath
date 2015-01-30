//��`
#define MAX_BONE_MATRICES 255

//�O���[�o��
Texture2D texDecal: register(t0);
SamplerState samLinear : register(s0);
SamplerState toonLinear : register(s1);

float4 m_LightDir = float4( 0, 1, 1, 1 );

cbuffer globalBuffer
{	
	matrix world;	//	���[���h�s��
	matrix wvp;		//	���[���h����ˉe�܂ł̕ϊ��s��
    matrix constBoneWorld[MAX_BONE_MATRICES];	//	�{�[���z��
};

//�X�L�j���O��̒��_�E�@��������
struct Skin
{
    float4 Pos;
    float3 Norm;
};

//	�o�[�e�b�N�X�o�b�t�@�[�̓���
struct VS_SkinIn
{
    float3 Pos	: POSITION;			//	���W
    float3 Norm : NORMAL;			//	�@��
    float2 Tex	: TEXCOORD;			//	�e�N�X�`�����W
    uint4  Bones : BONE_INDEX;		//	���_�ɑΉ������{�[���̃C���f�b�N�X
	float4 Weights : BONE_WEIGHT;	//	�{�[���̏d��
};

//�s�N�Z���V�F�[�_�[�̓���
struct PS_SkinIn
{
    float4 Pos	: SV_Position;		//	���W
    float3 Norm : NORMAL;			//	�@��
    float2 Tex	: TEXCOORD;			//	�e�N�X�`�����W
	float4 Color : COLOR0;			//	�o�̓J���[
};

/**
	�E�F�C�g�ɉ����Ē��_�ɑ΂���p���s����擾
 */
Skin SkinVert( VS_SkinIn Input )
{
	Skin Output = (Skin)0;

	float4 Pos = float4(Input.Pos,1);
	Pos.x*=-1;
    float3 Norm = Input.Norm;    

    //	�{�[��0
    uint iBone = Input.Bones.x;
    float fWeight = Input.Weights.x;
    matrix m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );    

    //	�{�[��1
    iBone = Input.Bones.y;
    fWeight = Input.Weights.y;
    m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );    

    //	�{�[��2
    iBone = Input.Bones.z;
    fWeight = Input.Weights.z;
    m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );    

    //	�{�[��3
    iBone = Input.Bones.w;
    fWeight = Input.Weights.w;
    m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );
    
    return Output;
}

/**
	���_�V�F�[�_�[
 */
PS_SkinIn SkinMeshVS( VS_SkinIn input )
{
    PS_SkinIn output;
    
	//	�擾�����p���s��𒸓_�Ɋ|�����킹��
    Skin vSkinned = SkinVert( input );
	//vSkinned.Pos.z *= -1;

	//	�s��ϊ������s
    output.Pos = mul( vSkinned.Pos, wvp );

	//	�@���̉�]
    output.Norm = normalize( mul( vSkinned.Norm, ( float3x3 )world ) );

	//	�e�N�X�`�����W�擾
    output.Tex = input.Tex;

    return output;
}

//	�s�N�Z���V�F�[�_�[
float4 SkinMeshPS(PS_SkinIn input) : SV_Target
{	
	//float4 Out;
//
	//// �n�[�t�����o�[�g�g�U�ؖ��ɂ�郉�C�e�B���O�v�Z
	//float p = dot( input.Norm, -m_LightDir.xyz );
	//p = p * 0.5f + 0.5f;
	////p = p * p;
//
	//// ************************************************************
	//// �g�D�[������
	//// ************************************************************
	//float4 Col = texDecal.Sample( toonLinear, float2( p, 0.0f ) );
//
	//Out = Col * texDecal.Sample( samLinear, input.Tex );
//
	//return Out;

	float4 TexDiffuse = texDecal.Sample ( samLinear, input.Tex );

	return TexDiffuse;
}