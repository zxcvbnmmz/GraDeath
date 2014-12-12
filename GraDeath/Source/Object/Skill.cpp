#include "Object/Skill.h"
#include "Loader/PlayerLoader.h"
#include "D2D/Sprite/Sprite.h"
#include <xutility>
#include "Utility/Converter.h"
#include <string>

void Skill::Init ( char* _filename )
{
	PlayerLoader::LoadFile ( _filename, &animSkill );
	currentCell = animSkill.cellDatas[ nowAnime ].begin ();
	skillAnim = std::shared_ptr< Sprite >( new Sprite );
	std::wstring filepass = L"";
	skillAnim->Create (L"");
}

void Skill::Update ()
{
	if ( ( *currentCell )->animFrame <= frameCount++ )
	{
		auto nextCell = currentCell + 1;
		if ( nextCell == animSkill.cellDatas[ nowAnime ].end () )
		{
			++nowAnime;
			currentCell = animSkill.cellDatas[ nowAnime ].begin ();
		}
		else
		{
			nowAnime = 0;
			currentCell = animSkill.cellDatas[ nowAnime ].begin ();
		}
	}
}

void Skill::Draw ()
{
	auto size = animSkill.cellSize;
	D2D1_RECT_F rect;
	size_t _pos = std::distance ( animSkill.cellDatas[ nowAnime ].begin (), currentCell );
	rect.left = size.x * _pos;
	rect.top = size.y * ( int )nowAnime;
	rect.right = size.x;
	rect.bottom = size.y;

	D3DXVECTOR2 texSize = animSkill.cellSize;
	skillAnim->SetTrimming ( rect );
	skillAnim->SetPosition ( pos.x * 32.0f, pos.y * 32.0f );
	skillAnim->SetSize ( texSize );
	skillAnim->Draw ( DRAW_RECT );
}

void Skill::SetPosition ( const D3DXVECTOR2& _pos )
{
	pos = _pos;
}

AnimationData& Skill::GetAnimationData ()
{
	return animSkill;
}