#include "Object/Skill/Skill.h"
#include "Loader/PlayerLoader.h"
#include "D2D/Sprite/Sprite.h"
#include <xutility>
#include "Utility/Converter.h"
#include <string>
#include <iostream>
#include <fstream>

void Skill::Init ( std::string _filename, std::wstring _path, int skill_id )
{
	PlayerLoader::LoadFile ( _filename.c_str (), &animSkill, skill_id );
	currentCell = animSkill.cellDatas[ nowAnime ].begin ();

	skillAnim = std::shared_ptr< Sprite >( new Sprite );

	char t[ 64 ];
	strncpy_s ( t, animSkill.fileName, animSkill.nameCount );	

	WCHAR f[ 40 ];
	Utility::ConvertToWChar ( f, t );
	//_path += f;

	skillAnim->Create ( _path.c_str() );// L"Resource/Object/Skill/WhiteBlack/skill01.png" );// f );
}

void Skill::Update ()
{
	if ( !skillFlg )
		return;

	int frame = ( *currentCell )->animFrame;
	if ( ( *currentCell )->animFrame <= frameCount++ )
	{
		auto nextCell = currentCell + 1;
		if ( nextCell == animSkill.cellDatas[ nowAnime ].end () )
		{
			//nowAnime = ( nowAnime + 1 ) % animSkill.cellDatas.size ();
			currentCell = animSkill.cellDatas[ nowAnime ].begin ();
			if ( nowAnime == ( animSkill.cellDatas.size () - 1 ) )
			{
				nowAnime = 0;
				skillFlg = false;
				currentCell = animSkill.cellDatas[ nowAnime ].begin ();
			}
			else
			{
				nowAnime++;
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
	if ( dirFlg == 1 )
		skillAnim->SetReverseFlag ( FLIP_HORIZONTAL );
	skillAnim->SetSize ( texSize );
	skillAnim->Draw ( DRAW_RECT );
}

void Skill::SetPosition ( const D3DXVECTOR2& _pos, unsigned int _dirFlg )
{
	dirFlg = _dirFlg;
	pos = _pos;
}

D3DXVECTOR2& Skill::GetPosition ()
{
	return pos;
}

void Skill::SkillOn ()
{
	skillFlg = true;
}

void Skill::SkillOff ()
{
	skillFlg = false;
}

AnimationData& Skill::GetAnimationData ()
{
	return animSkill;
}