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
    std::vector<std::shared_ptr<Sprite>> sprite_animes;
	std::shared_ptr<Sprite> sprite_anime;
    std::vector<std::shared_ptr<Sprite>> Special_SKILLs;
    std::shared_ptr<Sprite> Special_BLUE;
    float HP = 20.f + rand() % 10;
    bool Stageflg = false;
    int StageCoolTime = 0;
    int count = 0;
    int playernum = 0;
    int SpecialSkillTime = 0;
    bool SkillEnd = false;
}

void CreateWorldEdge();
void CreateEachStage(int stageLevel = 1);
b2Vec2 StageGetPos();
b2Vec2 StageGetSize();

namespace{
	b2Body* screenEdgeBody;
	b2Body* breakableStage;
	b2Body* unbreakableStage;
    b2Body* GetBreakbleStage();
    b2Body* GetUnbreakbleStage();
}

bool Stage::Initialize(int stageID){
	CreateWorldEdge();

	CreateEachStage(stageID);

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
#ifdef _DEBUG
    if (Keyboard::CheckKey(KC_ENTER) == INPUT_PUSH || HP <= 0){
        HP = 0;
        //@ x 1366* y 768
        Stageflg = true;
    }
#endif

    if (Stageflg == true){
        StageCoolTime++;
        sprite_anime->SetTrimming(0, 0 + (768 * count), 1366, 768);
        /*
        switch ()
        {
        default:
        break;
        }
        */
        
        D3DXVECTOR2 pos = Special_BLUE->GetPosition();
        if (pos.y != 0)
            Special_BLUE->SetPositionY(pos.y-5);
        Special_BLUE->Draw();
    }
    if (StageCoolTime > 10){
        StageCoolTime = 0;
        count++;
        if (count > 5){
            count = 6;
            if (SpecialSkillTime == 0)
                SpecialSkillTime = 10;
            if (SpecialSkillTime > 0)
                SpecialSkillTime--;
            if (SpecialSkillTime == 0)
                CriateStage();
        }
        
    }

#ifdef _DEBUG
    if (Keyboard::CheckKey(KC_P) == INPUT_PUSH)
        CriateStage();
#endif
    
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
    World::DestoryBody(breakableStage);
	for ( auto& obj : sprites )
		Util::safeDelete ( obj );
	for ( auto& bg : bgSprite )
		Util::safeDelete ( bg );
	for (auto& anime : sprite_animes)
		anime.reset();
    for (auto& SKILL : Special_SKILLs)
        SKILL.reset();
    sprites.clear();
	sprite_animes.clear();
	bgSprite.clear();
    CriateStage();
    Special_SKILLs.clear();
}

void CreateWorldEdge(){
	b2BodyDef def;
    screenEdgeBody = World::CreateBody(&def);
    breakableStage = World::CreateBody(&def);

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
	//screenEdgeShape.Set(upperLeftCorner, upperRightCorner);
	//screenEdgeBody->CreateFixture(&screenEdgeShape, density)->SetFilterData(filter);
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
    fixture = breakableStage->CreateFixture(&screenEdgeShape, density);
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

    switch (stageLevel)
    {
    default:
        Sprite* sprite = new Sprite;

        /*各種パラメータの設定*/
        sprite->Create(L"Resource/Scene/Game/Stage/Stage.png");
        D3DXVECTOR2 pos(0, 580);
        sprite->SetPosition(pos);
        //@ x 1366* y 768
        sprite->SetTrimming(0, 575, 1366, 193);
        D2D1_SIZE_F size;
        size.height = 193.f;
        size.width = 1366.f;
        sprite->SetSize(size);
        sprites.push_back(sprite);

        //アニメーション用
		sprite_anime.reset(new Sprite);
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

        Special_BLUE.reset(new Sprite);
        Special_BLUE->Create(L"Resource/Scene/Game/Stage/blue_SSKILL.png");
        D3DXVECTOR2 SKILLpos(0, 400);
        Special_BLUE->SetPosition(SKILLpos);
        //@ x 1366* y 768
        Special_BLUE->SetTrimming(0, 0, 1366, 768);
        D2D1_SIZE_F SKILL_size;
        SKILL_size.height = 768.f;
        SKILL_size.width = 1366.f;
        Special_BLUE->SetSize(SKILL_size);
        Special_SKILLs.push_back(Special_BLUE);


        Sprite* sprite1 = new Sprite;
        sprite1->Create(L"Resource/Scene/Game/Stage/bg01.png");
        bgSprite.push_back(sprite1);
        Sprite* sprite2 = new Sprite;
        sprite2->Create(L"Resource/Scene/Game/Stage/bg02.png");
        bgSprite.push_back(sprite2);
        Sprite* sprite3 = new Sprite;
        sprite3->Create(L"Resource/Scene/Game/Stage/bg03.png");
        bgSprite.push_back(sprite3);
        Sprite* Special_BLUE = new Sprite;
        

        for (auto& bg : bgSprite)
            bg->SetPosition(0, 0);
        break;
    }
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

bool Stage::GetSkillEnd(){
    return SkillEnd;
}
/*
この後はコリジョンを外して入れるだけ
*/
//void DettachFixture(b2Body* body);
//void Stage::AttachFixture(){
//    // 新しいフィクスチャーを作る前に一旦前のを消しておく
//    DettachFixture(body);
//
//    // 各セルに配置されたCollisionShapeを新しいフィクスチャーとして全てbodyに追加する
//    for (auto shape : shapes){
//        shape->AddFixture(body);
//    }
//}
//
//void DettachFixture(b2Body* body){
//    b2Fixture* fixture = body->GetFixtureList();
//    if (fixture == nullptr){
//        return;
//    }
//
//    while (fixture != nullptr){
//        b2Fixture* temp = fixture->GetNext();
//        body->DestroyFixture(fixture);
//        fixture = temp;
//    }
//}