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
    std::vector<Sprite*> sprite_animes;
	Sprite* sprite_anime = new Sprite;
    float HP = 20.f + rand() % 10;
    bool Stageflg = false;
    int StageCoolTime = 0;
    int count = 0;
    int playernum = 0;
}

void CreateWorldEdge();
void CreateEachStage(int stageLevel = 1);
b2Vec2 StageGetPos();
b2Vec2 StageGetSize();

namespace{
	b2Body* screenEdgeBody;
	b2Body* breakableStage;
	b2Body* unbreakableStage;
}

bool Stage::Initialize(int stageID){
	CreateWorldEdge();

	CreateEachStage();

	return true;
}

void Stage::Draw(){
	bgSprite[ 0 ]->Draw ();
	bgSprite[ 1 ]->Draw ();
    if (Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH  || HP <= 0 ){
        HP = 0;
        //@ x 1366* y 768
        Stageflg = true;
    }
    if (Stageflg == true){
        StageCoolTime++;
        sprite_anime->SetTrimming(0, 0 + (768 * count), 1366, 768);
    }
    if (StageCoolTime > 10){
        StageCoolTime = 0;
        count++;
        if (count > 5){
            count = 6;
        }
    }
    if (Keyboard::CheckKey(KC_P) == INPUT_PUSH)
        CriateStage();

    if (Stageflg == false){
        for (Sprite* sprite : sprites){
            sprite->Draw(DRAW_RECT);
        }
    }
    else{
        sprite_anime->Draw(DRAW_RECT);
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
    for (auto& anime : sprite_animes)
        Util::safeDelete(anime);
	bgSprite.clear();
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
	b2Vec2 upperLeftCorner = b2Vec2(0, 0);
	b2Vec2 upperRightCorner = b2Vec2(widthInMeters, 0);
	b2Vec2 lowerLeftCorner = b2Vec2(0, heightInMeters);
	b2Vec2 lowerRightCorner = b2Vec2(widthInMeters, heightInMeters);

	b2Filter filter;
	filter.groupIndex = 1;
	filter.categoryBits = 0x0001;
	filter.maskBits = 0xffff;

	// 上辺
	screenEdgeShape.Set(upperLeftCorner, upperRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density)->SetFilterData(filter);
	// 下辺
	screenEdgeShape.Set(lowerLeftCorner, lowerRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density)->SetFilterData(filter);
	// 左辺
	screenEdgeShape.Set(upperLeftCorner, lowerLeftCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density)->SetFilterData(filter);
	// 右辺
	screenEdgeShape.Set(upperRightCorner, lowerRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density)->SetFilterData(filter);


    //Stageの当たり判定
    screenEdgeShape.Set(StageGetPos(), StageGetSize());
    b2Fixture* fixture = screenEdgeBody->CreateFixture(&screenEdgeShape, density);
    fixture->SetFilterData(filter);

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
        Sprite* sprite = new Sprite;

        /*各種パラメータの設定*/
		sprite->Create ( L"Resource/Scene/Game/Stage/Stage.png" );
		D3DXVECTOR2 pos ( 0, 580 );
		sprite->SetPosition ( pos );
        //@ x 1366* y 768
        sprite->SetTrimming (0,575,1366,193);
        D2D1_SIZE_F size;
        size.height = 193.f;
        size.width = 1366.f;
        sprite->SetSize(size);
        sprites.push_back(sprite);

        //アニメーション用
        sprite_anime->Create(L"Resource/Scene/Game/Stage/Stage.png");
        D3DXVECTOR2 animepos(0, 0);
        sprite_anime->SetPosition(animepos);
        //@ x 1366* y 768
        sprite_anime->SetTrimming(0, 0, 1366, 768);
        D2D1_SIZE_F anime_size;
        anime_size.height = 768.f;
        anime_size.width = 1366.f;
        sprite_anime->SetSize(anime_size);
        sprite_animes.push_back(sprite_anime);
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

b2Vec2 StageGetPos(){
    return b2Vec2(0, 19);
}
b2Vec2 StageGetSize(){
    return b2Vec2(42, 19);
}

float Stage::GetStageHP(){
    return HP;
}

void StageDamage(float _damage, int _playernum){
    HP = HP - _damage;
    playernum = _playernum;
}
void SetStageHP(float _HP){
    HP = _HP;
}

void Stage::CriateStage(){
    Stageflg = false;
    count = 0;
    //            D3DXVECTOR2 pos(0, 580);
    //            sprite_anime->SetPosition(pos);
    //@ x 1366* y 768
    sprite_anime->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F size;
    size.height = 768.f;
    size.width = 1366.f;
    sprite_anime->SetSize(size);
    HP = 20.f + rand() % 10;
}

bool Stage::GetStageStatus(){
    if (GetStageHP() <= 0){
        return false;
    }
    return true;
}

int Stage::StageBrakePlayerNum(){
    return playernum;
}

b2Body* Stage::GetBreakbleStage(){
	return breakableStage;
}

b2Body* Stage::GetUnbreakbleStage(){
	return unbreakableStage;
}

