// ************************************************************
// fliename	CwnSkinMesh.cpp
// brief	�Ǝ��t�H�[�}�b�g�X�L�����b�V��
// name		����@�T
// memo
// 2013.10.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Graphic/D3DGraphic.h"
#include "Model/CwnSkinMesh.h"
#include "Model/CwnDecoder.h"
//#include "Shader.h"
//#include "Model/ModelSkinShader.h"
#include "Model/MeshDef.h"

#include "Graphic/Sampler/Sampler.h"
#include "Graphic/ShaderResource/ShaderResource.h"


// �R���X�g���N�^
CwnSkinMesh::CwnSkinMesh() : bindBone( 0 ), nowBone( 0 ), animeData( 0 )
{
	animeFrame = 0;
}

// �f�X�g���N�^
CwnSkinMesh::~CwnSkinMesh()
{
}

void CwnSkinMesh::SetAnimeData( AnimeData* inData )
{
	animeData	= inData;
	animeFrame	= animeData->animeStart;
}

// �`��
void CwnSkinMesh::Render( Shader* shader, ModelSkinConstantBuffer* fscb )
{
	if ( !meshData ) return;

	int tempNumMesh = meshData->numMesh < (unsigned)animeData->numMesh ? meshData->numMesh : (unsigned)animeData->numMesh;
	//for ( DWORD num = 0; num < meshData->numMesh; num++ )
	for ( int num = 0; num < tempNumMesh; num++ )
	{
		SubRender( num, meshData->meshs[ num ], shader, fscb );
	}
}

// �T�u�`��
void CwnSkinMesh::SubRender( int num, CwnMesh& mesh, Shader* shader, ModelSkinConstantBuffer* fscb )
{
	//ModelSkinConstantBuffer temp;
	// �V�F�[�_�[�ɓn�����߂̃����o�ϐ��ɃR�s�[
	for ( DWORD j = 0; j < animeData->animes[ num ].numBone; j++ )
	{
		// �s��擾
		D3DXMATRIX mat = GetCurrentPoseMatrix( num, j, animeFrame * animeData->animes[ num ].numBone + j );

		// �V�F�[�_�[�ɓn���̂œ]�u�s��Ƃ���
		D3DXMatrixTranspose( &mat, &mat );

		// �s����R�s�[
		//fscb->bone[ j ] = mat;
	}
	// ���_�o�b�t�@���Z�b�g
	mesh.vertexBuffer.SetToIA();
	// �C���f�b�N�X�o�b�t�@���Z�b�g
	mesh.indexBuffer.SetToIA ();

	Sampler sampler;

	for ( DWORD i = 0; i < mesh.numMaterial; i++ )
	{	
		//shader->SetConstantBuffer( fscb );

		if ( mesh.material[ mesh.subSet[ i ].matIndex ].m_texture != NULL )
		{
			// �T���v�����O�X�e�[�g��n��
			sampler.SetLinearWrap ();

			// �e�N�X�`����n��
			meshData->meshs[ num ].material[ meshData->meshs[ num ].subSet[ i ].matIndex ].m_texture->SetToShader ( 0, 1 );
		}

		// �v���~�e�B�u�E�g�|���W�[��ݒ�
		Graphic::D3D::IA::SetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		// �}�e���A���̊e�v�f���G�t�F�N�g�ɓn��
		Graphic::D3D::Draw (
			mesh.subSet[ i ].faceCount,
			mesh.subSet[ i ].faceStart,
			0 );
	}
}

// ���݂̎p���s����擾
D3DXMATRIX CwnSkinMesh::GetCurrentPoseMatrix ( int num, int bindIndex, int nowIndex )
{
	D3DXMATRIX inv;

	//	FBX�̃o�C���h�|�[�Y�̋t�s����擾
	D3DXMatrixInverse( &inv, 0, &animeData->animes[ num ].bindPose[ bindIndex ] );

	// �o�C���h�|�[�Y�̋t�s��ƃt���[���p���s���������B
	D3DXMATRIX ret = inv * animeData->animes[ num ].nowPose[ nowIndex ];

	return ret;
}

// �A�j���t���[���̉��Z
void CwnSkinMesh::AddAnimeCount( int frame )
{
	animeFrame += frame;
	
	// �X�^�[�g�^�C�����ꎞ�ύX�I�I�I�I
	if ( animeFrame >= animeData->animeStop )
		animeFrame = animeData->animeStart;//animeCntStart;
}

// �A�j���t���[���̃Z�b�g
void CwnSkinMesh::SetAnimeCount( int frame )
{
	animeFrame = frame % animeData->animeStop;
}

// �A�j���[�V�����J�E���g�̏I���m�F
bool CwnSkinMesh::GetAnimeEnd()
{
	return animeFrame == ( animeData->animeStop - 1 );
}

int CwnSkinMesh::GetAnimeFrameEnd()
{
	return animeData->animeStop;
}