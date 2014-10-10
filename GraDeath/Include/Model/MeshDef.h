// ************************************************************
// fliename	FBXDef.h
// brief	FBX�ÓI�V�F�[�_
// name		����@�T
// memo
// 2013.06.11
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_MESH_DEF_H_
#define	_MESH_DEF_H_

//#define FBXSDK_NEW_API

// �C���N���[�h ***********************************************
#include <D3DX10math.h>
//#include "Core.h"
//#include "Typedefs.h"
//#include "Texture.h"
//#include "VertexBuffer.h"
//#include "IndexBuffer.h"

// �O���錾 ***************************************************
namespace Graphic
{
	class ShaderResource;
}

// Graphic�̎d�l�錾 ******************************************
using namespace Graphic;


// ************************************************************
// struct	MeshVertex
// brief	���b�V�����_�\����
//
// variable
// Vector3			: pos				: �ʒu
// Vector3			: normal			: �@��
// Vector2			: uv				: UV���W
// UINT				: boneIndex[4]		: �{�[���ԍ�
// float			: boneWeight[4]		: �{�[���̏d��
// ************************************************************ 
struct MeshVertex
{
	D3DXVECTOR3	pos;
	D3DXVECTOR3	normal;
	D3DXVECTOR3	uv;
	UINT		boneIndex[ 4 ];
	float		boneWeight[ 4 ];

	MeshVertex()
	{
		ZeroMemory( this, sizeof( MeshVertex ) );
	}
};

// ************************************************************
// struct	MeshBone
// brief	�{�[���\����
//
// variable
// Matrix			: bindPose			: �Œ肵�Ă���|�[�Y
// Matrix			: nowPose			: ���݂̃|�[�Y
// ************************************************************
struct MeshBone
{
	D3DXMATRIX	bindPose;
	D3DXMATRIX	nowPose;

	MeshBone()
	{
		ZeroMemory( this, sizeof( MeshBone ) );
	}
};

// ************************************************************
// struct	MeshSubSet
// brief	���b�V���̃T�u�Z�b�g
//
// variable
// UINT				: matIndex			: �|���S���ԍ� 
// UINT				: faceStart			: 3�̒��_�̂����A���Ԗڂ�
// UINT				: faceCount			: �����Ă���|���S����
// ************************************************************
struct MeshSubSet
{
	unsigned int matIndex;
	unsigned int faceStart;
	unsigned int faceCount;

	MeshSubSet()
	{
		ZeroMemory( this, sizeof( MeshSubSet ) );
	}
};

// ************************************************************
// struct	MeshMaterial
// brief	�}�e���A���\����
//
// variable
// Vector4			: ambient			: �A���r�G���g
// Vector4			: diffuse			: �f�B�t���[�Y
// Vector4			: specular			: �X�y�L����
// float			: alpha				: ����
// float			: power				: ����
// DWORD			: dwNumFace;		: �}�e���A���̎����Ă���|���S����
// Texture			: m_texture;		: �e�N�X�`��
// wchar_t			: textureName[100]	: �e�N�X�`���̖��O
// char				: matName[256]		: �}�e���A���̖��O
// ************************************************************
struct MeshMaterial
{
	D3DXVECTOR4			ambient;			// �A���r�G���g
	D3DXVECTOR4			diffuse;			// �f�B�t���[�Y
	D3DXVECTOR4			specular;			// �X�y�L����
	float				alpha;				// ����
	float				power;				// ����
	unsigned long		dwNumFace;			// �}�e���A���̎����Ă���|���S����

	ShaderResource*		m_texture;			// �e�N�X�`��
	
	wchar_t				textureName[ 20 ];	// �e�N�X�`���̖��O
	char				matName[ 20 ];		// �}�e���A���̖��O

	MeshMaterial()
	{
		ZeroMemory( this, sizeof( MeshMaterial ) );
	}
};

// ************************************************************
// struct	Mesh
// brief	���b�V���\����
//
// variable
// DWORD			: numVert			: ���_��
// DWORD			: numFace			: �ʐ�
// DWORD			: numUV				: UV��
// DWORD			: numMaterial		: �}�e���A����
// DWORD			: numSub			: �T�u�Z�b�g�̐�
// DWORD			: numChild			: �q����
// Mesh**			: childMesh			: �q�̃��b�V��
// FbxNode*			: node				: �m�[�h�f�[�^
// VertexBuffer		: vertexBuffer		: ���_�o�b�t�@
// IndexBuffer*		: indexBuffer		: �C���f�b�N�X�o�b�t�@
// MeshMaterial*	: material;			: �}�e���A��
// MeshSubSet*		: subSet;			: �T�u�Z�b�g
// Matrix			: parentOrientation	: �e�̎p���s��
// Matrix			: world;			: ���b�V���̍ŏI�I�ȃ��[���h�s��
// Matrix			: orientation;		: �p���s��
// int				: numBone;			: �{�[����
// MeshBone*		: boneArray;		: �Ǝ��{�[���f�[�^�z��
// FbxCluster**		: cluster;			: �N���X�^�[
// Matrix			: boneData[255]		: �V�F�[�_�[�ɓn�����߂̃{�[���z��
// ************************************************************
//struct Mesh
//{
//	// ���b�V���֘A
//	unsigned long			numVert;
//	unsigned long			numFace;
//	unsigned long			numUV;
//	unsigned long			numMaterial;
//	unsigned long			numSub;
//	unsigned long			numChild;
//
//	// ���b�V���֘A
//	Mesh**			childMesh;
//
//	// �o�b�t�@�֘A
//	//VertexBuffer	vertexBuffer;
//	//IndexBuffer*	indexBuffer;
//
//	// �}�e���A���֘A
//	MeshMaterial*	material;
//	MeshSubSet*		subSet;
//	
//	//	�s��֘A
//	D3DXMATRIX		parentOrientation;
//	D3DXMATRIX		world;
//	D3DXMATRIX		orientation;
//
//
//	// FBX�֘A
//	int				numBone;
//	MeshBone*		boneArray;
//	D3DXMATRIX		boneData[ 255 ];
//
//};

// ************************************************************
// �Ǝ��p���b�V��
// brief	�Ǝ��p���b�V���̍\����
// ************************************************************
struct CwnMesh
{
	// ���b�V���֘A
	unsigned long			numVert;		// �o�[�e�b�N�X��
	unsigned long			numFace;		// �ʐ�
	unsigned long			numMaterial;	// �}�e���A����
	unsigned long			numSub;			// �T�u�Z�b�g��

	// �o�b�t�@�֘A
	//VertexBuffer	vertexBuffer;	// ���_�o�b�t�@
	//IndexBuffer		indexBuffer;	// �C���f�b�N�X�o�b�t�@

	MeshVertex*		vertexList;		// �x�[�e�b�N�X���X�g
	int*			indexList;		// �C���f�b�N�X���X�g

	MeshMaterial*	material;		// �}�e���A����
	MeshSubSet*		subSet;			// �T�u�Z�b�g��

	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	CwnMesh() : material( 0 ), subSet( 0 ){}
};

// ************************************************************
// �Ǝ��p���b�V���f�[�^
// brief	�Ǝ��p���b�V���f�[�^�̍\����
// ************************************************************
struct MeshData
{
	char			modelName[ 20 ];	// ���f����
	unsigned long	numMesh;			// ���b�V����
	unsigned long	numBone;			// �{�[����
	int				animeStart;			// �A�j���t���[���̊J�n
	int				animeStop;			// �A�j���t���[���̏I���

	CwnMesh*		meshs;				// ���b�V���̓��I�z��

	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	MeshData() : meshs( 0 ){}
};

// ************************************************************
// struct	AnimeData
// brief	�A�j���[�V�����f�[�^�̍\����
// ************************************************************
struct CwnAnime
{
	unsigned long	numBone;

	D3DXMATRIX*		bindPose;
	D3DXMATRIX*		nowPose;

};

// ************************************************************
// struct	AnimeData
// brief	�A�j���[�V�����f�[�^�̍\����
// ************************************************************
struct AnimeData
{
	int		animeStart;
	int		animeStop;
	int		numMesh;

	CwnAnime* animes;

	AnimeData() :  animes( 0 ){}
};

// ************************************************************
// ���b�V���e�N�X�`������ւ��p�\����
// brief	���b�V���e�N�X�`������ւ��p
// ************************************************************
struct MeshTexture
{
	unsigned long		numMat;
	ShaderResource*		texture;

	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	MeshTexture() : texture( 0 ){}
};

// ************************************************************
// �e�N�X�`���A�^�b�`�\����
// brief	���b�V���e�N�X�`������ւ��p
// ************************************************************
struct MeshTextures
{
	unsigned long	numMesh;
	MeshTexture*	texData;

	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	MeshTextures() : texData( 0 ){}
};

namespace ModelTexture
{

// ************************************************************
// �e�N�X�`���A�^�b�`�\���̂̐���
// brief �e�N�X�`���͐������Ȃ�
// ************************************************************
extern void CreateMeshTextures( MeshTextures* outTextures, const MeshData* inData );

// ************************************************************
// �e�N�X�`���A�^�b�`�\���̂̉��
// ************************************************************
extern void DeleteMeshTextures( MeshTextures* textures );

}

#endif