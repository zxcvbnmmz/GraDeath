#include "Object/Skill.h"
#include "Loader/PlayerLoader.h"
#include "D2D/Sprite/Sprite.h"
#include <xutility>
#include "Utility/Converter.h"
#include <string>
#include <iostream>
#include <fstream>

void Skill::Init ( char* _filename )
{
	PlayerLoader::LoadFile ( _filename, &animSkill );
	currentCell = animSkill.cellDatas[ nowAnime ].begin ();

	skillAnim = std::shared_ptr< Sprite >( new Sprite );

	char t[ 64 ];
	strncpy_s ( t, animSkill.fileName, animSkill.nameCount );	
	char path[ 64 ] = "Resource/Object/Skill/WhiteBlack/";
	strcat_s ( path, t );

	WCHAR f[ 80 ];
	Utility::ConvertToWChar ( f, path );

	skillAnim->Create ( L"Resource/Object/Skill/WhiteBlack/skill01.png" );// f );
}

void Skill::Update ()
{
	if ( !skillFlg )
		return;

	if ( ( *currentCell )->animFrame <= frameCount++ )
	{
		auto nextCell = currentCell + 1;
		if ( nextCell == animSkill.cellDatas[ nowAnime ].end () )
		{
			nowAnime = ( nowAnime + 1 ) % animSkill.cellDatas.size ();
			currentCell = animSkill.cellDatas[ nowAnime ].begin ();
			if ( nowAnime == ( animSkill.cellDatas.size () - 1 ) )
			{
				nowAnime = 0;
				skillFlg = false;
				currentCell = animSkill.cellDatas[ nowAnime ].begin ();
			}
		}
		else
		{
			currentCell++;
			frameCount = 0;
		}
	}
}

void Skill::Draw ()
{
	if ( !skillFlg )
		return;

	auto size = animSkill.cellSize;
	D2D1_RECT_F rect;
	size_t _pos = std::distance ( animSkill.cellDatas[ nowAnime ].begin (), currentCell );
	rect.left = size.x * _pos;
	rect.top = size.y * ( int )nowAnime;
	rect.right = size.x;
	rect.bottom = size.y;

	D3DXVECTOR2 texSize = animSkill.cellSize;
	skillAnim->SetTrimming ( rect );
	skillAnim->SetPosition ( pos.x, pos.y );
	skillAnim->SetSize ( texSize );
	skillAnim->Draw ( DRAW_RECT );
}

void Skill::SetPosition ( const D3DXVECTOR2& _pos )
{
	pos = D3DXVECTOR2 ( _pos.x * 32.0f, ( _pos.y  * 32.0f ) - 290.0f );
}

void Skill::SkillOn ()
{
	skillFlg = true;
}

AnimationData& Skill::GetAnimationData ()
{
	return animSkill;
}