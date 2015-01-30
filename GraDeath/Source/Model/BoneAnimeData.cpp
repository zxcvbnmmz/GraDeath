// ************************************************************
// filename	BoneAnimeData.cpp
// brief	�Ǝ��t�H�[�}�b�g�A�j���[�V�����s��̎擾
// name		����@�T
// memo
// 2013.09.13
// ************************************************************

// �C���N���[�h ***********************************************
#include "Model/BoneAnimeData.h"
#include "Utility/SafeDelete.h"
#include <fstream>


// ************************************************************
// struct	CwnMatrix
// brief	�Ǎ��p�ȈՍs��
// ************************************************************
struct CwnMatrix
{
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};

// �R���X�g���N�^
BoneAnimeData::BoneAnimeData(){}

// �f�X�g���N�^
BoneAnimeData::~BoneAnimeData()
{
	animeArray.clear();
	//Release();
}

// ���
void BoneAnimeData::Release()
{
	// �󂾂ƍs��Ȃ�
	if ( animeArray.empty() )
		return;

	std::vector< AnimeData* >::iterator cur = animeArray.begin();

	while ( cur != animeArray.end() )
	{
		if ( ( *cur ) != NULL )
		{
			for ( DWORD num = 0; num < (unsigned)( *cur )->numMesh; num++ )
			{
				Util::safeDeleteArray ( ( *cur )->animes[ num ].bindPose );
				Util::safeDeleteArray ( ( *cur )->animes[ num ].nowPose );
			}
			Util::safeDeleteArray ( ( *cur )->animes );
			delete *cur;
			cur = animeArray.erase( cur );
			continue;
		}
		++cur;
	}
}

// �A�j���[�V�����f�[�^�̓Ǎ�
bool BoneAnimeData::LoadAnime( char* filename )
{
	std::ifstream ifs( filename, std::ios::binary );

	if( ifs.fail() ) return false;

	AnimeData* tempData = new AnimeData;

	// ���b�V�����̎擾
	ifs.read( ( char* )&tempData->numMesh, sizeof( DWORD ) );

	// �A�j���[�V�����̃t���[�����̍ŏ��ƍŌ�̎擾
	DWORD startTime, stopTime;
	ifs.read( ( char* )&startTime, sizeof( DWORD ) );
	ifs.read( ( char* )&stopTime, sizeof( DWORD ) );
	tempData->animeStart	= ( int )startTime;
	tempData->animeStop	= ( int )stopTime;

	// ���b�V�����s����쐬
	tempData->animes = new CwnAnime[ tempData->numMesh ];

	// ���b�V�����̎p���s��𐶐�
	for ( int num = 0; num < tempData->numMesh; num++ )
	{
		// �{�[�����擾
		ifs.read( ( char* )&tempData->animes[ num ].numBone, sizeof( DWORD ) );

		CwnMatrix* bindBone	= 0;
		CwnMatrix* nowBone	= 0;

		// �o�C���h�s��
		bindBone = new CwnMatrix[ tempData->animes[ num ].numBone ];
		ifs.read( ( char* )bindBone, sizeof( CwnMatrix ) * tempData->animes[ num ].numBone );

		// �p���s��
		nowBone = new CwnMatrix[ tempData->animes[ num ].numBone * tempData->animeStop ];
		ifs.read( ( char* )nowBone, sizeof( CwnMatrix ) * tempData->animes[ num ].numBone * tempData->animeStop );

		// �{�[���̓Ǎ�
		LoadBone( bindBone, nowBone, tempData, num );

		delete[] bindBone;
		delete[] nowBone;
	}

	animeArray.push_back( tempData );

	return true;
}

// �{�[���s��̓Ǎ�
void BoneAnimeData::LoadBone( CwnMatrix* bindBone, CwnMatrix* nowBone, AnimeData* animeData, int num )
{
	animeData->animes[ num ].bindPose = new D3DXMATRIX[ animeData->animes[ num ].numBone ];

	for ( DWORD i = 0; i < animeData->animes[ num ].numBone; i++ )
	{
		CopyMatrix( bindBone[ i ], animeData->animes[ num ].bindPose[ i ] );
	}

	animeData->animes[ num ].nowPose = new D3DXMATRIX[ animeData->animes[ num ].numBone * animeData->animeStop ];

	for ( int cnt = 0; cnt < animeData->animeStop; cnt++ )
	{
		// �{�[���̐������[�v���s
		for ( DWORD i = 0; i < animeData->animes[ num ].numBone; i++ )
		{
			CopyMatrix( nowBone[ cnt * animeData->animes[ num ].numBone + i ], animeData->animes[ num ].nowPose[ cnt * animeData->animes[ num ].numBone + i ] );
		}
	}
}

// �s��̃R�s�[
void BoneAnimeData::CopyMatrix ( CwnMatrix& inMat, D3DXMATRIX& outMat )
{
	outMat._11 = inMat._11; outMat._12 = inMat._12; outMat._13 = inMat._13; outMat._14 = inMat._14;
	outMat._21 = inMat._21; outMat._22 = inMat._22; outMat._23 = inMat._23; outMat._24 = inMat._24;
	outMat._31 = inMat._31; outMat._32 = inMat._32; outMat._33 = inMat._33; outMat._34 = inMat._34;
	outMat._41 = inMat._41; outMat._42 = inMat._42; outMat._43 = inMat._43; outMat._44 = inMat._44;
}

// �e�A�j���[�V�����z��̃R�s�[
void BoneAnimeData::CopyAnimeData( BoneAnimeData* setBoneAnimeData )
{
	Release();

	std::vector< AnimeData* >* tempArray = setBoneAnimeData->GetAnimeArray();
	int size = tempArray->size();
	animeArray.resize( size );

	for ( int i = 0; i < size; i++ )
	{
		animeArray[ i ] = ( *tempArray )[ i ];
	}
}

// ���݂̃A�j���[�V�����f�[�^�z����擾
std::vector< AnimeData* >* BoneAnimeData::GetAnimeArray()
{
	return &animeArray;
}

// �A�j���[�V�����̒ǉ�
void BoneAnimeData::PushAnimation( AnimeData* _anime )
{
	animeArray.push_back( _anime );
}