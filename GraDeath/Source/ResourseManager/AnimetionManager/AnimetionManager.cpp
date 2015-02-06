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

		// メッシュ数の取得
		ifs.read ( ( char* )&tempData->numMesh, sizeof( DWORD ) );

		// ボーン情報取得
		//ifs.read( ( char* )&tempData->numBone, sizeof( DWORD ) );

		// アニメーションのフレーム数の最初と最後の取得
		DWORD startTime, stopTime;
		ifs.read ( ( char* )&startTime, sizeof( DWORD ) );
		ifs.read ( ( char* )&stopTime, sizeof( DWORD ) );
		tempData->animeStart = ( int )startTime;
		tempData->animeStop = ( int )stopTime;

		// メッシュ分行列を作成
		tempData->animes = new CwnAnime[ tempData->numMesh ];

		// メッシュ分の姿勢行列を生成
		for ( int num = 0; num < tempData->numMesh; num++ )
		{
			// ボーンの書き出し
			ifs.read ( ( char* )&tempData->animes[ num ].numBone, sizeof( DWORD ) );

			D3DXMATRIX* bindBone = 0;
			D3DXMATRIX* nowBone = 0;

			// バインド行列
			bindBone = new D3DXMATRIX[ tempData->animes[ num ].numBone ];
			ifs.read ( ( char* )bindBone, sizeof( D3DXMATRIX )* tempData->animes[ num ].numBone );

			// 姿勢行列
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