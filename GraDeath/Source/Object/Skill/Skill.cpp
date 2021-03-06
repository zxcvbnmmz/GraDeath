#include "Object/Skill/Skill.h"
#include "Loader/PlayerLoader.h"
#include "D2D/Sprite/Sprite.h"
#include <xutility>
#include "Utility/Converter.h"
#include"Object/CollisionShape.h"
#include <string>
#include <iostream>
#include <fstream>
#include <Box2D\Dynamics\b2Body.h>
#include "World/World.h"


void SkillDettachFixture ( b2Body* body );

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

//	b2BodyDef def;
//	def.position = b2Vec2 ( pos.x, pos.y );
//	def.type = b2_staticBody;

//	body = World::CreateBody ( &def );
//	body->SetUserData ( this );
}

void Skill::Update ( b2Body* _body )
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
				SkillDettachFixture ( _body );
			}
            else
            {
                nowAnime = (nowAnime + 1) % animSkill.cellDatas.size();
                currentCell = animSkill.cellDatas[nowAnime].begin();
				SetAttachFixture ( _body );
				if ( dirFlg )
					Reverse ();
            }

		}
		else
		{
			currentCell++;
			SetAttachFixture ( _body );
			if ( dirFlg )
				Reverse ();
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
	//if ( dirFlg == 1 )
		skillAnim->SetReverseFlag ( (REVERSE_FLAG)dirFlg );
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

//b2Body& Skill::Getb2Body ()
//{
//	return *body;
//}

bool Skill::IsActive ()
{
	return skillFlg;
}

void Skill::SetAttachFixture ( b2Body* _body )
{
	// 新しいフィクスチャーを作る前に一旦前のを消しておく
	SkillDettachFixture ( _body );

	// 各セルに配置されたCollisionShapeを新しいフィクスチャーとして全てbodyに追加する
	for ( auto shape : ( *currentCell )->shapes ){
		shape->AddFixture ( _body );
	}
	if ( dirFlg )
		Reverse ();
}

//void Skill::AttachFixture ( std::vector<std::shared_ptr<CollisionShape>>& shapes )
//{
//	// 新しいフィクスチャーを作る前に一旦前のを消しておく
//	SkillDettachFixture ( body );

	// 各セルに配置されたCollisionShapeを新しいフィクスチャーとして全てbodyに追加する
//	for ( auto shape : shapes ){
//		shape->AddFixture ( body );
//	}
//}

void SkillDettachFixture ( b2Body* body ){
	b2Fixture* fixture = body->GetFixtureList ();
	if ( fixture == nullptr ){
		return;
	}

	while ( fixture != nullptr ){
		b2Fixture* temp = fixture->GetNext ();
		body->DestroyFixture ( fixture );
		fixture = temp;
	}
}

void Skill::Reverse ()
{
	for ( auto shape : ( *currentCell )->shapes )
	{
		shape->Reverse ();
	}
}