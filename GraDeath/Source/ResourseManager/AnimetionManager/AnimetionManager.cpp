#include "ResourseManager/AnimetionManager/AnimetionManager.h"
#include "Model/MeshDef.h"
#include <fstream>

namespace AnimationManager{
	bool LoadAnime ( char* filename );
	void LoadBone ( D3DXMATRIX* bindBone, D3DXMATRIX* nowBone, AnimeData* animeData );

	struct Data{
		AnimeData* animationData;
		const char* tag;
		Data* next;
		Data* prev;
		Data () :next ( nullptr ), prev ( nullptr ){}
	};

	namespace{
		Data first;
	};

	AnimeData* Get ( const char* tag ){
		Data* data = first.next;

		while ( data != nullptr ){
			if ( !strcmp ( data->tag, tag ) ){
				return data->animationData;
			}
			data = data->next;
		}

		return nullptr;
	}

	bool Load ( const char* fileName, const char* tag ){
		Data* data = &first;
		Data* next = data->next;

		if ( !strcmp ( tag, "" ) ){
			tag = fileName;
		}

		while ( next ){
			if ( !strcmp ( next->tag, tag ) ){
				return true;
			}
			next = next->next;
		}

		std::ifstream ifs ( fileName, std::ios::binary );

		if ( ifs.fail () ) return false;

		AnimeData* tempData = new AnimeData;

		// ���b�V�����̎擾
		ifs.read ( ( char* )&tempData->numMesh, sizeof( DWORD ) );

		// �{�[�����擾
		//ifs.read( ( char* )&tempData->numBone, sizeof( DWORD ) );

		// �A�j���[�V�����̃t���[�����̍ŏ��ƍŌ�̎擾
		DWORD startTime, stopTime;
		ifs.read ( ( char* )&startTime, sizeof( DWORD ) );
		ifs.read ( ( char* )&stopTime, sizeof( DWORD ) );
		tempData->animeStart = ( int )startTime;
		tempData->animeStop = ( int )stopTime;

		// ���b�V�����s����쐬
		tempData->animes = new CwnAnime[ tempData->numMesh ];

		// ���b�V�����̎p���s��𐶐�
		for ( int num = 0; num < tempData->numMesh; num++ )
		{
			// �{�[���̏����o��
			ifs.read ( ( char* )&tempData->animes[ num ].numBone, sizeof( DWORD ) );

			D3DXMATRIX* bindBone = 0;
			D3DXMATRIX* nowBone = 0;

			// �o�C���h�s��
			bindBone = new D3DXMATRIX[ tempData->animes[ num ].numBone ];
			ifs.read ( ( char* )bindBone, sizeof( D3DXMATRIX )* tempData->animes[ num ].numBone );

			// �p���s��
			nowBone = new D3DXMATRIX[ tempData->animes[ num ].numBone * tempData->animeStop ];
			ifs.read ( ( char* )nowBone, sizeof( D3DXMATRIX )* tempData->animes[ num ].numBone * tempData->animeStop );

			tempData->animes[ num ].bindPose = bindBone;
			tempData->animes[ num ].nowPose = nowBone;
		}

		data = &first;
		next = data->next;
		while ( next != nullptr ){
			data = next;
			next = next->next;
		}
		next = new Data;
		next->animationData = tempData;
		next->tag = tag;
		data->next = next;
		next->prev = data;

		return true;
	}

	void Release (){
		Data* data = first.next;
		while ( data != nullptr ){
			Data* temp = data->next;

			AnimeData* animeData = data->animationData;

			for ( int i = 0; i < animeData->numMesh; i++ )
			{
				delete[ ] animeData->animes[ i ].bindPose;
				delete[ ] animeData->animes[ i ].nowPose;
			}
			delete[ ] animeData->animes;

			delete animeData;

			delete data;
			data = nullptr;
			data = temp;
		}
	}

	bool Release ( const char* tag ){
		Data* data = first.next;
		while ( data != nullptr ){
			if ( !strcmp ( data->tag, tag ) ){
				Data* prev = data->prev;
				prev->next = data->next;
				if ( data->next )
					data->next->prev = prev;

				AnimeData* d = data->animationData;

				for ( int i = 0; i < d->numMesh; i++ )
				{
					delete[ ] d->animes[ i ].bindPose;
					delete[ ] d->animes[ i ].nowPose;
				}
				delete[ ] d->animes;
				//delete[] d->bindPose;
				//delete[] d->nowPose;

				delete data;
				data = nullptr;
				return true;
			}
			data = data->next;
		}
		return false;
	}
};