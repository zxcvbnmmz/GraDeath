#include <iostream>
#include <fstream>
#include "Loader/PlayerLoader.h"
#include "Object/ObjectParameter.h"
#include <assert.h>
#include <string>

// ƒAƒjƒ[ƒVƒ‡ƒ“‚Ìƒ‹[ƒv
struct AnimationData
{
	char	annimaType;
	char	animaCount;
	char	effectCount;
	char*	effectFile;
	char	soundCount;
	char*	soudnFile;
	char	shortformCount;
};

struct ShortFormData
{
	char	collisionModel;
	char	collisionType;
	char	strength;
	int		left;
	int		top;
	unsigned int	right;	// lŠp‚È‚ç‰¡•A‰~‚È‚ç”¼Œa
	unsigned int	bottom; // lŠp‚È‚çc•A‰~‚È‚ç0
};

char* playerIconName[ ] =
{
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
	"Resource/Object/Player/TestData.bin",
};

namespace PlayerLoader
{

	void LoadFile ( const char* _filename, ObjectParameter& parameter )
	{
		std::ifstream ifs ( _filename, std::ios::binary );

		assert ( !ifs.fail () );
		
		char temp;
		ifs.read ( ( char* )&temp, sizeof( char ) );
		parameter.count = static_cast< int >( temp );

		parameter.fileName = std::shared_ptr<char> ( new char[ parameter.count ], []( char* str ){
			delete[] str;
			str = nullptr;
		} );
		ifs.read ( ( char* )parameter.fileName.get(), sizeof( char )* parameter.count );

		ifs.read ( ( char* )&temp, sizeof( char ) );
		parameter.widthLength = static_cast< int >( temp );

		ifs.read ( ( char* )&temp, sizeof( char ) );
		int h_count = static_cast< int >( temp );
		parameter.heightLength = static_cast< int >( temp );
	}

	char* GetLoadFileName ( CharacterInfo::PLAYER_TYPE _type )
	{
		return playerIconName[ _type ];
	}
};