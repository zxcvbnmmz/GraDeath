#include "Stage/Stage.h"
#include "World/World.h"
#include "System/Window.h"
#include <Box2D\Box2D.h>
#include "D2D/Sprite/Sprite.h"
#include <vector>
#include <algorithm>
#include <functional>
#include "Utility/SafeDelete.h"
#include <stdio.h>
#include "Input\Keyboard.h"

namespace{
	const static float PTM_RATIO = 32.0f;
	std::vector<Sprite*> sprites;
	std::vector<Sprite*> bgSprite;
    Sprite* sprite = new Sprite;
    float HP = 20.f + rand() % 10;
}

void CreateWorldEdge();
void CreateEachStage(int stageLevel = 1);

namespace{
	b2Body* screenEdgeBody;
}

bool Stage::Initialize(int stageID){
	CreateWorldEdge();

	CreateEachStage();

	return true;
}

void Stage::Draw(){
	bgSprite[ 0 ]->Draw ();
	bgSprite[ 1 ]->Draw ();
    if (Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH){
        HP = 0;
//        for (int i = 1; i < 6; i++){
            //@ x 1366* y 768
            sprite->SetTrimming(0, 575 * 2, 1366, 193);
            D2D1_SIZE_F size;
            size.height = 193.f;
            size.width = 1366.f;
            sprite->SetSize(size);
            sprites.push_back(sprite);
 //        }
    }
	for ( Sprite* sprite : sprites ){
        sprite->Draw(DRAW_RECT);
	}
	bgSprite[ 2 ]->Draw ();
}

void GetDamage(float _damage){
    HP -= _damage;
}

void Stage::Release(){
	World::DestoryBody(screenEdgeBody);
	for ( auto& obj : sprites )
		Util::safeDelete ( obj );
	for ( auto& bg : bgSprite )
		Util::safeDelete ( bg );
}

void CreateWorldEdge(){
	b2BodyDef def;
	screenEdgeBody = World::CreateBody(&def);

	b2EdgeShape screenEdgeShape;
	float density = 0.0f;
	int windowWidth, windowHeight;
	System::Window::GetWindowSize(&windowWidth, &windowHeight);

	float widthInMeters = (float)windowWidth / (float)PTM_RATIO;
	float heightInMeters = (float)windowHeight / (float)PTM_RATIO;
	b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
	b2Vec2 lowerRightCorner = b2Vec2(widthInMeters, 0);
	b2Vec2 upperLeftCorner = b2Vec2(0, heightInMeters);
	b2Vec2 upperRightCorner = b2Vec2(widthInMeters, heightInMeters);

	// 上辺
	screenEdgeShape.Set(upperLeftCorner, upperRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density);
	// 下辺
	screenEdgeShape.Set(lowerLeftCorner, lowerRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density);
	// 左辺
	screenEdgeShape.Set(upperLeftCorner, lowerLeftCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density);
	// 右辺
	screenEdgeShape.Set(upperRightCorner, lowerRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density);
}

void CreateEachStage(int stageLevel){
	/*

	int level;
	struct StageFixtures{
		float pos[2][8];
		int count
	};

	std::list<StageFixture>& stageObjects = StageLoader::GetFixture();


	
	for (int i = 0; i < 100; ++i){
		b2PolygonShape polygon;
		polygon.Set(b2Vec2(pos[0][i],pos[1][i]);
	}
	*/

	int spriteNum = 1;

	for (int i = 0; i < spriteNum; ++i){
		/*各種パラメータの設定*/
		sprite->Create ( L"Resource/Scene/Game/Stage/Ground.png" );
		D3DXVECTOR2 pos ( 0, 580 );
		sprite->SetPosition ( pos );
        //@ x 1366* y 768
        sprite->SetTrimming (0,575,1366,193);
        D2D1_SIZE_F size;
        size.height = 193.f;
        size.width = 1366.f;
        sprite->SetSize(size);
        sprites.push_back(sprite);
	}

	Sprite* sprite1 = new Sprite;
	sprite1->Create ( L"Resource/Scene/Game/Stage/bg01.png" );
	bgSprite.push_back ( sprite1 );
	Sprite* sprite2 = new Sprite;
	sprite2->Create ( L"Resource/Scene/Game/Stage/bg02.png" );
	bgSprite.push_back ( sprite2 );
	Sprite* sprite3 = new Sprite;
	sprite3->Create ( L"Resource/Scene/Game/Stage/bg03.png" );
	bgSprite.push_back ( sprite3 );
	for ( auto& bg : bgSprite )
		bg->SetPosition ( 0, 0 );
}




