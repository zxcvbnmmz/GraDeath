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

char* playerIconName[ ] =
{
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
};


namespace PlayerLoader
{
	//void LoadShapeData ( std::ifstream* _ifs, short _count, std::vector< std::shared_ptr< ShapeData > > _shapeData );

	void LoadFile ( const int _num, AnimationData* parameter )
	{
		std::ifstream ifs ( playerIconName[_num], std::ios::binary );

		assert ( !ifs.fail () );

		char hedCount;
		ifs.read ( ( char* )&hedCount, sizeof( char ) );
		int count = static_cast< int >( hedCount );

		parameter->fileName = new char[ count ];
		ifs.read ( ( char* )parameter->fileName, sizeof( char )* count );

		ifs.read ( ( char* )&hedCount, sizeof( char ) );
		parameter->rectWCount = static_cast< int >( hedCount );

		ifs.read ( ( char* )&hedCount, sizeof( char ) );
		parameter->rectHCount = static_cast<int>(hedCount);

		char t[64];
		strncpy_s(t, parameter->fileName, count);
		char path[64] = "Resource/Object/Player/";
		strcat_s(path, t);

		WCHAR f[80];
		Utility::ConvertToWChar(f, path);
		D3DXVECTOR2 size;
		GetTextureSize(f, &size);
		parameter->cellSize = D3DXVECTOR2(size.x / parameter->rectWCount, size.y / parameter->rectHCount);

		for ( int i = 0; i < parameter->rectHCount; i++ )
		{
			std::vector< std::shared_ptr< CellData > > cellData;
			for ( int j = 0; j < parameter->rectWCount; j++ )
			{
				std::shared_ptr< CellData > cell = std::shared_ptr< CellData > ( new CellData );
				char temp = 0;

				// �Z�����g�p���邩
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->animUse = static_cast< short >( temp );

				// 1���Ƃ��̃Z���͎g�p���Ȃ�
				if ( cell->animUse )
					continue;

				// �A�j���[�V�����^�C�v
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->animType = static_cast< short >( temp );

				// �g�p����t���[����
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->animFrame = static_cast< short >( temp );

				short fileCount = 0;
				// �G�t�F�N�g�̕�����
				ifs.read ( ( char* )&temp, sizeof( char ) );
				fileCount = static_cast< short >( temp );
				//ifs.read ( ( char* )&temp, sizeof( char ) );
				//cell->effectCount = static_cast< short >( temp );

				// �G�t�F�N�g���擾
				char* effectName = new char[ fileCount ];
				ifs.read ( ( char* )effectName, sizeof( char )* fileCount );
				delete[] effectName;
				//cell->effectFile = new char[ cell->effectCount ];
				//ifs.read ( ( char* )cell->effectFile, sizeof( char )* cell->effectCount );

				// �T�E���h�̕�����
				ifs.read ( ( char* )&temp, sizeof( char ) );
				fileCount = static_cast< short >( temp );
				//ifs.read ( ( char* )&temp, sizeof( char ) );
				//cell->soundCount = static_cast< short >( temp );

				// �T�E���h���擾
				char* soundName = new char[ fileCount ];
				ifs.read ( ( char* )soundName, sizeof( char )* fileCount );
				delete[ ] soundName;
				//cell->soundFile = new char[ cell->soundCount ];
				//ifs.read ( ( char* )cell->soundFile, sizeof( char )* cell->effectCount );

				// shape�J�E���g
				ifs.read ( ( char* )&temp, sizeof( char ) );
				cell->shapeCount = static_cast< short >( temp );

				//LoadShapeData ( &ifs, cell->shapeCount, cell->shapeData );
				for ( int k = 0; k < cell->shapeCount; k++ )
				{
					auto shape = std::shared_ptr<ShapeData> ( new ShapeData );
					// ���ǉ�
					std::shared_ptr<CollisionShape> collisionShape;

					char tempShape = 0;

					// �����蔻��̃��f��
					ifs.read ( ( char* )&tempShape, sizeof( char ) );
					shape->collisionModel = static_cast< short >( tempShape );

					// �����蔻��̎��
					ifs.read ( ( char* )&tempShape, sizeof( char ) );
					shape->collisionType = static_cast< short >( tempShape );

					// ����
					ifs.read ( ( char* )&tempShape, sizeof( char ) );
					shape->strength = static_cast< short >( tempShape );

					if ( shape->collisionModel )
					{// �^���Ɖ~
						CircleDef def;

						// ���SX
						ifs.read ( ( char* )&shape->shape.circle.x, sizeof( int ) );
						// ���SY
						ifs.read ( ( char* )&shape->shape.circle.y, sizeof( int ) );
						// ���a
						ifs.read ( ( char* )&shape->shape.circle.rad, sizeof( int ) );

						// ���ǉ�
						def.r = shape->shape.circle.rad;
						def.x = shape->shape.circle.x;
						def.y = shape->shape.circle.y;
						collisionShape = std::make_shared<CollisionShape>(def);
					}
					else
					{// �U���Ǝl�p
						SquareDef def;
						for ( int l = 0; l < 4; l++ )
						{
							// ���SX
							ifs.read ( ( char* )&shape->shape.square.x[ l ], sizeof( int ) );
							// ���SY
							ifs.read ( ( char* )&shape->shape.square.y[ l ], sizeof( int ) );
						}

						// ���ǉ�
						memcpy ( def.x, shape->shape.square.x, sizeof( int )* 4 );
						memcpy ( def.y, shape->shape.square.y, sizeof( int )* 4 );
						collisionShape.reset ( new CollisionShape ( def ) );
					}
					cell->shapeData.push_back ( shape );

					// ���ǉ�
					cell->shapes.push_back(collisionShape);
				}
				cellData.push_back ( cell );
			}
			// �Z���f�[�^��push
			parameter->cellDatas.push_back ( cellData );
		}
	}

	//char* GetLoadFileName ( CharacterInfo::PLAYER_TYPE _type )
	////{
	//	return playerIconName[ _type ];
	//}
};