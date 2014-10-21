// ************************************************************
// fliename	CwnSkinMesh.h
// brief	�Ǝ��t�H�[�}�b�g�X�L�����b�V��
// name		����@�T
// memo
// 2013.10.21
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_CWN_SKINMESH_H_
#define	_CWN_SKINMESH_H_

// �C���N���[�h ***********************************************
#include "Model/CwnBaseMesh.h"
#include <D3DX10math.h>


// �O���錾 ***************************************************
class D3DGraphics;
class Shader;
struct ModelSkinConstantBuffer;
struct CwnMesh;
struct AnimeData;


// ************************************************************
// class	CwnSkinMesh
// brief	�Ǝ��t�H�[�}�b�g�Ǎ�
// ************************************************************
class CwnSkinMesh : public CwnBaseMesh{
private:
	// D3DGraphics���玩�R�ɃA�N�Z�X�\�ɂ���
	friend class D3DGraphics;

	D3DXMATRIX		boneData[ 255 ];	// �{�[���s��

	int				animeFrame;			// �A�j���[�V�����t���[��

	AnimeData*		animeData;

	D3DXMATRIX*		bindBone;			// �o�C���h�s��
	D3DXMATRIX*		nowBone;			// �p���s��
	int				animeCntStart;		// �A�j���[�V�����J�E���g�J�n
	int				animeCntEnd;		// �A�j���[�V�����J�E���g�I��

public:
	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	CwnSkinMesh();

	// ************************************************************
	// �f�X�g���N�^
	// ************************************************************
	~CwnSkinMesh();

	// ************************************************************
	// �A�j���t���[���̉��Z
	// brief �X�L�����b�V���݂̂Ŏg�p
	// ************************************************************
	void AddAnimeCount( int frame );

	// ************************************************************
	// �A�j���t���[���̃Z�b�g
	// brief �X�L�����b�V���݂̂Ŏg�p
	// ************************************************************
	void SetAnimeCount( int frame );

	// ************************************************************
	// �A�j���f�[�^�̃Z�b�g
	// brief �X�L�����b�V���݂̂Ŏg�p
	// state	: type			: name			- memo
	// in		: Matrix*		: inBind		- �o�C���h�s��
	// in		: Matrix*		: inNow			- �p���s��
	// in		: int			: startCount	- �A�j���[�V�����J�E���g�̊J�n
	// in		: int			: endCount		- �A�j���[�V�����J�E���g�̏I��
	// ************************************************************
	void SetAnimeData( AnimeData* inData );

	// ************************************************************
	// �A�j���[�V�����J�E���g�̏I���m�F
	// brief �X�L�����b�V���݂̂Ŏg�p
	// ************************************************************
	bool GetAnimeEnd();

	int GetAnimeFrameEnd();

	// ************************************************************
	// �W���C���g�̍s��擾
	// brief �X�L�����b�V���݂̂Ŏg�p
	// ************************************************************
	const D3DXMATRIX GetJointMatrix ( int mum );

	// ************************************************************
	// �`��
	// ************************************************************
	void Render( Shader* shader, ModelSkinConstantBuffer* fscb );

private:
	// ************************************************************
	// �T�u�`��
	// ************************************************************
	void SubRender( int num, CwnMesh& mesh, Shader* shader, ModelSkinConstantBuffer* fscb );

	// ************************************************************
	// ���݂̎p���s����擾
	// ************************************************************
	D3DXMATRIX GetCurrentPoseMatrix ( int num, int bindIndex, int nowIndex );

};

#endif