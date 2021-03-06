#include <iostream>
#include <fstream>
#include "Loader/PlayerLoader.h"
#include "Object/ObjectParameter.h"
#include <assert.h>
#include <string>
#include "Utility/Converter.h"

#include "Object/CollisionShape.h"
#include "Utility/SizeGetter.h"
#include "Utility/Converter.h"
#include "Object/ObjectMask.h"
#include "Sound/Sound.h"

char* playerIconName[ ] =
{
	"Resource/Object/Player/R.bin",
	"Resource/Object/Player/B.bin",
	"Resource/Object/Player/Y.bin",
	"Resource/Object/Player/WB.bin",
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
};
/*
PLAYER_RED = 0,
PLAYER_BLUE,
PLAYER_YELLOW,
PLAYER_GRAY,
*/
/*
char skillPassName[5][64] =
{
	"Resource/Object/Skill/WhiteBlack/",
	"Resource/Object/Skill/Red/",
	"Resource/Object/Skill/Yellow/",
	"Resource/Object/Skill/Blue/",
	"Resource/Object/Player/",
};
*/
namespace PlayerLoader
{
	enum
	{
		_PLAYER_TYPE,
		_SKILL_TYPE
	};

	void Load ( const char* filename, AnimationData* parameter, int _type ,float scale);

	void LoadFile ( const int _num, AnimationData* parameter, float scale)
	{
		Load ( playerIconName[ _num ], parameter, SKILL_ID_MAX, scale);
	}

	void LoadFile(const char* filename, AnimationData* parameter, int skill_id, float scale)
	{
		Load ( filename, parameter, skill_id, scale);
	}

	void Load ( const char* filename, AnimationData* parameter, int _type, float scale )
	{
		std::ifstream ifs ( filename, std::ios::binary );

		assert ( !ifs.fail () );

		char hedCount;
		ifs.read ( ( char* )&hedCount, sizeof( char ) );
		int count = static_cast< int >( hedCount );
		parameter->nameCount = count;

		//char path[2][64] = {
		//	"Resource/Object/Player/",
		//	"Resource/Object/Skill/WhiteBlack/" };

		char path[ 5 ][ 64 ] =
		{
			"Resource/Object/Skill/Red/",
			"Resource/Object/Skill/Blue/",
			"Resource/Object/Skill/Yellow/",
			"Resource/Object/Skill/WhiteBlack/",
			"Resource/Object/Player/",
		};

		int s = count + strlen ( path[ _type ] );
		parameter->fileName = new char[ count + strlen ( path[ _type ] ) + 1 ];
		ifs.read ( ( char* )parameter->fileName, sizeof( char )* count );

		ifs.read ( ( char* )&hedCount, sizeof( char ) );
		parameter->rectWCount = static_cast< int >( hedCount );

		ifs.read ( ( char* )&hedCount, sizeof( char ) );
		parameter->rectHCount = static_cast<int>( hedCount );

		char t[ 64 ];
		strncpy_s ( t, parameter->fileName, count );
		strcat_s ( path[ _type ], t );

		WCHAR f[ 80 ];
		Utility::ConvertToWChar ( f, path[ _type ] );
		D3DXVECTOR2 size;
		GetTextureSize ( f, &size );
		parameter->cellSize = D3DXVECTOR2 ( size.x / parameter->rectWCount, size.y / parameter->rectHCount );

		int s2 = strlen ( path[ _type ] );
		strcpy_s ( parameter->fileName, strlen ( path[ _type ] ) + 1, path[ _type ] );

		for ( int i = 0; i < parameter->rectHCount; i++ )
		{
			std::vector< std::shared_ptr< CellData > > cellData;
			for ( int j = 0; j < parameter->rectWCount; j++ )
			{
				std::shared_ptr< CellData > cell = std::shared_ptr< CellData > ( new CellData );
				char temp = 0;

				// セルを使用するか
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->animUse = static_cast< short >( temp );

				// 1だとそのセルは使用しない
				if ( cell->animUse )
					continue;

				// アニメーションタイプ
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->animType = static_cast< short >( temp );

				// 使用するフレーム数
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->animFrame= static_cast< short >(temp);
				//cell->animFrame = rand() % 3 + 5;

				short fileCount = 0;
				// エフェクトの文字数
				ifs.read ( ( char* )&temp, sizeof( char ) );
				fileCount = static_cast< short >( temp );

				// エフェクト名取得
				char* effectName = new char[ fileCount ];
				ifs.read ( ( char* )effectName, sizeof( char )* fileCount );
				delete[ ] effectName;

				// サウンドの文字数
				ifs.read ( ( char* )&temp, sizeof( char ) );
				fileCount = static_cast< short >( temp );

				// サウンド名取得
				char* soundName = new char[ fileCount ];
				ZeroMemory(soundName,sizeof(char)*fileCount);
				ifs.read ( ( char* )soundName, sizeof( char )* fileCount );
				if (temp > 0){
					std::string voicePath = "Resource\\Voice\\";
					char temp[80];
					strncpy_s(temp, soundName, sizeof(char)*fileCount);
					voicePath += temp;
					cell->se = Sound::CreateSE(const_cast<char*>(voicePath.c_str()));
				}
				delete[ ] soundName;

				// shapeカウント
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->shapeCount = static_cast< short >( temp );

				for ( int k = 0; k < cell->shapeCount; k++ )
				{
					auto shape = std::shared_ptr<ShapeData> ( new ShapeData );
					// 仮追加
					std::shared_ptr<CollisionShape> collisionShape;

					char tempShape = 0;

					// あたり判定のモデル
					ifs.read ( ( char* )&tempShape, sizeof( char ) );
					shape->collisionModel = static_cast< short >( tempShape );

					// あたり判定の種類
					ifs.read ( ( char* )&tempShape, sizeof( char ) );
					shape->collisionType = static_cast< short >( tempShape );

					// 強さ
					ifs.read ( ( char* )&tempShape, sizeof( char ) );
					shape->strength = static_cast< short >( tempShape );

					if ( shape->collisionModel )
					{// 真だと円
						CircleDef def;

						// 中心X
						ifs.read ( ( char* )&shape->shape.circle.x, sizeof( int ) );
						// 中心Y
						ifs.read ( ( char* )&shape->shape.circle.y, sizeof( int ) );
						// 半径
						ifs.read ( ( char* )&shape->shape.circle.rad, sizeof( int ) );

						// 仮追加
						def.r = shape->shape.circle.rad/2.0f;
						def.x = shape->shape.circle.x;
						def.y = shape->shape.circle.y;
						def.categoryBit = categoryBits[shape->collisionType];
						if (SKILL_ID_MAX == _type){
							def.maskBit = MASK_COL_ATK_DEF;
							def.groupIndex = 1;
						}
						else{
							def.categoryBit = 0;
							def.maskBit = 0;
							def.groupIndex = -1;
						}
						def.strength = shape->strength;
						def.width = (float)(size.x / parameter->rectWCount);
						def.height = (float)(size.y / parameter->rectHCount);
						def.scale = scale;

						collisionShape.reset(new CollisionShape(def));
					}
					else
					{// 偽だと四角
						SquareDef def;
						for ( int l = 0; l < 4; l++ )
						{
							// 中心X
							ifs.read ( ( char* )&shape->shape.square.x[ l ], sizeof( int ) );
							// 中心Y
							ifs.read ( ( char* )&shape->shape.square.y[ l ], sizeof( int ) );
						}

						// 仮追加
						memcpy ( def.x, shape->shape.square.x, sizeof( int )* 4 );
						memcpy ( def.y, shape->shape.square.y, sizeof( int )* 4 );
						def.categoryBit = categoryBits[shape->collisionType];
						//def.categoryBit = MASK_COL_ATK_DEF;
						if (SKILL_ID_MAX == _type){
							def.maskBit = MASK_COL_ATK_DEF;
							def.groupIndex = 1;
						}
						else{
							def.categoryBit = 0;
							def.maskBit = 0;
							def.groupIndex = -1;
						}
						def.strength = shape->strength;
						def.width = (float)(size.x / parameter->rectWCount);
						def.height = (float)(size.y / parameter->rectHCount);
						def.scale = scale;

						collisionShape.reset(new CollisionShape(def));
					}
					cell->shapeData.push_back ( shape );

					// 仮追加
					cell->shapes.push_back ( collisionShape );
				}
				cellData.push_back ( cell );
			}
			// セルデータのpush
			parameter->cellDatas.push_back ( cellData );
		}
	}
};