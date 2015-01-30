// ************************************************************
// fliename	CwnBaseMesh.cpp
// brief	�Ǝ��t�H�[�}�b�g�x�[�X���b�V��
// name		����@�T
// memo
// 2013.10.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Model/CwnBaseMesh.h"
#include "Model/CwnDecoder.h"
#include "Model/MeshDef.h"
#include "Utility/SafeDelete.h"
#include "Graphic/ShaderResource/ShaderResource.h"



// �R���X�g���N�^
CwnBaseMesh::CwnBaseMesh() : decoder( nullptr ), meshData( 0 ){}

// �f�X�g���N�^
CwnBaseMesh::~CwnBaseMesh()
{
	Release();
}

// ���
void CwnBaseMesh::Release()
{
	Util::safeDelete ( decoder );
}

// �Ǎ�
bool CwnBaseMesh::LoadCwn( char* filename, char* path )
{
	// ���ɍ���Ă�����^��Ԃ�
	if ( decoder ) return true;

	decoder = new CwnDecoder;
	bool ret = decoder->LoadCwn( filename, path );

	if ( ret )
	{
		meshData = decoder->GetMesh();
	}
	return  ret;
}

// ���b�V���f�[�^�̎擾
const MeshData* CwnBaseMesh::GetMesh()
{
	if ( !meshData )
		return nullptr;
	return meshData;
}

// �e�N�X�`���̃A�^�b�`
bool CwnBaseMesh::SetAttachingTexture( const MeshTextures* textures )
{
	if ( !meshData ) 
		return false;

	if ( meshData->numMesh != textures->numMesh )
		return false;

	for ( unsigned long i = 0; i < meshData->numMesh; i++ )
	{
		if ( meshData->meshs[ i ].numMaterial != textures->texData[ i ].numMat )
			return false;

		for ( unsigned int k = 0; k < meshData->meshs[ i ].numMaterial; k++ )
		{
			meshData->meshs[ i ].material[ k ].m_texture = textures->texData[ i ].texture;
		}
	}
	return true;
}

bool CwnBaseMesh::SetAttachingTexture( Graphic::ShaderResource* inTexture )
{
	if ( !meshData )
		return false;

	for ( unsigned long i = 0; i < meshData->numMesh; i++ )
	{
		for ( unsigned int k = 0; k < meshData->meshs[ i ].numMaterial; k++ )
		{
			if ( meshData->meshs[ i ].material[ k ].m_texture != 0 )
			{
				Util::safeDelete ( meshData->meshs[ i ].material[ k ].m_texture );
			}
			meshData->meshs[ i ].material[ k ].m_texture = inTexture;
		}
	}
	return true;
}

bool CwnBaseMesh::SetAttachingTexture ( Graphic::ShaderResource* inTexture, int numMesh, int numMat )
{
	if ( !meshData ) 
		return false;
	if ( ( unsigned )numMesh >= meshData->numMesh ) 
		return false;
	if ( (unsigned)numMat >= meshData->meshs[ numMesh ].numMaterial ) 
		return false;

	if ( meshData->meshs[ numMesh ].material[ numMat ].m_texture != 0 )
	{
		Util::safeDelete ( meshData->meshs[ numMesh ].material[ numMat ].m_texture );
	}
	meshData->meshs[ numMesh ].material[ numMat ].m_texture = inTexture;
	return true;
}