#include "Stage/Stage.h"
#include "World/World.h"
#include "System/Window.h"
#include <Box2D\Box2D.h>
#include "D2D/Sprite/Sprite.h"
//#include "Object/CollisionShape.h"
#include <vector>
#include <algorithm>
#include <functional>
#include "Utility/SafeDelete.h"
#include <stdio.h>
#include "Input\Keyboard.h"
#include "Direction/Fade.h"
#include "Sound/SE/SE.h"

namespace{
	const static float PTM_RATIO = 32.0f;
	std::vector<Sprite*> sprites;
	std::vector<Sprite*> bgSprite;
    std::vector<std::shared_ptr<Sprite>> sprite_animes;
	std::shared_ptr<Sprite> sprite_anime;
    std::vector<std::shared_ptr<Sprite>> Special_SKILLs;
    std::shared_ptr<Sprite> Special_BLUE;
    std::shared_ptr<Sprite> Special_RED;
    std::shared_ptr<Sprite> Special_YELLOW;
    std::shared_ptr<Sprite> Special_SIROKURO;

    float HP = 500.f + rand() % 500;
    bool Stageflg = false;
    int StageCoolTime = 0;
    int counter = 0;
    int playernum = 0;
    bool SkillEnd = false;
    int SpecialSkillTime = 0;
    std::shared_ptr<Fade> fade;
    std::shared_ptr<Fade> Suppression_fade;
    float Suppressioncount = 0;
    float SuppressionScale = 1;
    bool isSuppressionScale = false;
    bool isSuppression = false;
    bool fadeflg = false;
    int StageID = 0;
    int Charatype = 0;
    SE RedSkillSE;
    SE BlueSkillSE;
    SE YellowSkillSE;
    SE SiroKuroSkillSE;
    SE NoCollarSkillSE;

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

bool Stage::Initialize(int _stageID){
	CreateWorldEdge();

	CreateEachStage(_stageID);
    fade.reset(new Fade(L"Resource/Texture/white.png"));
    fade->SetAlpha(0);
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
        sprite_anime->SetTrimming(0, 0 + (768 * counter), 1366, 768);
        /*
        switch ()
        {
        default:
        break;
        }
        */
        
        D3DXVECTOR2 pos = GetSpecialSkillpos(Charatype);
        
        if (pos.y != 0)
            SetSpecialSkill(Charatype, pos.y - 3);
        StageDraw(Charatype);
    }
    if (StageCoolTime > 10){
        StageCoolTime = 0;
        counter++;
        fade->AddAlpha(0.1f);
        fadeflg = true;
        if (counter > 5){
            counter = 6;
            if (SpecialSkillTime == 0)
                SpecialSkillTime = 10;
            if (SpecialSkillTime > 0)
                SpecialSkillTime--;
            if (SpecialSkillTime == 0){
                CriateStage();
                SkillEnd = true;
                
            }
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
    Special_BLUE.reset();
    RedSkillSE->Release();
    BlueSkillSE->Release();
    YellowSkillSE->Release();
    SiroKuroSkillSE->Release();
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
/*
    b2Vec2 StageGetPos(){
        return b2Vec2(0, 19);
    }
    b2Vec2 StageGetSize(){
        return b2Vec2(42, 19);
    }
*/
    //Stageの当たり判定
    screenEdgeShape.Set(StageGetPos(), StageGetSize());
    b2Fixture* fixture = breakableStage->CreateFixture(&screenEdgeShape, density);
    screenEdgeShape.Set(StageGetPos(), lowerLeftCorner);
    fixture = breakableStage->CreateFixture(&screenEdgeShape, density);
    screenEdgeShape.Set(lowerLeftCorner, lowerRightCorner);
    fixture = breakableStage->CreateFixture(&screenEdgeShape, density);
    screenEdgeShape.Set(StageGetPos(), lowerRightCorner);
    fixture = breakableStage->CreateFixture(&screenEdgeShape, density);
    fixture->SetFilterData(filter);
}

void CreateRedStage(Sprite* _sprite){
    _sprite->Create(L"Resource/Scene/Game/Stage/RedStage.png");
    D3DXVECTOR2 pos(0, 0);
    _sprite->SetPosition(pos);
    //@ x 1366* y 768
    _sprite->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F size;
    size.height = 768.f;
    size.width = 1366.f;
    _sprite->SetSize(size);
    sprites.push_back(_sprite);

    //アニメーション用
    sprite_anime.reset(new Sprite);
    sprite_anime->Create(L"Resource/Scene/Game/Stage/RedStage.png");
    D3DXVECTOR2 animepos(0, 0);
    sprite_anime->SetPosition(animepos);
    //@ x 1366* y 768
    sprite_anime->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F anime_size;
    anime_size.height = 768.f;
    anime_size.width = 1366.f;
    sprite_anime->SetSize(anime_size);
    sprite_animes.push_back(sprite_anime);

    Sprite* sprite1 = new Sprite;
    sprite1->Create(L"Resource/Scene/Game/Stage/Redbg1.png");
    bgSprite.push_back(sprite1);
    Sprite* sprite2 = new Sprite;
    sprite2->Create(L"Resource/Scene/Game/Stage/Redbg2.png");
    bgSprite.push_back(sprite2);
    Sprite* sprite3 = new Sprite;
    sprite3->Create(L"Resource/Scene/Game/Stage/Redbg3.png");
    bgSprite.push_back(sprite3);


    for (auto& bg : bgSprite)
        bg->SetPosition(0, 0);
}
void CreateBlueStage(Sprite* _sprite){
    _sprite->Create(L"Resource/Scene/Game/Stage/BlueStage.png");
    D3DXVECTOR2 pos(0, 0);
    _sprite->SetPosition(pos);
    //@ x 1366* y 768
    _sprite->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F size;
    size.height = 768.f;
    size.width = 1366.f;
    _sprite->SetSize(size);
    sprites.push_back(_sprite);

    //アニメーション用
    sprite_anime.reset(new Sprite);
    sprite_anime->Create(L"Resource/Scene/Game/Stage/BlueStage.png");
    D3DXVECTOR2 animepos(0, 0);
    sprite_anime->SetPosition(animepos);
    //@ x 1366* y 768
    sprite_anime->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F anime_size;
    anime_size.height = 768.f;
    anime_size.width = 1366.f;
    sprite_anime->SetSize(anime_size);
    sprite_animes.push_back(sprite_anime);

    Sprite* sprite1 = new Sprite;
    sprite1->Create(L"Resource/Scene/Game/Stage/Bluebg1.png");
    bgSprite.push_back(sprite1);
    Sprite* sprite2 = new Sprite;
    sprite2->Create(L"Resource/Scene/Game/Stage/Bluebg2.png");
    bgSprite.push_back(sprite2);
    Sprite* sprite3 = new Sprite;
    sprite3->Create(L"Resource/Scene/Game/Stage/Bluebg3.png");
    bgSprite.push_back(sprite3);


    for (auto& bg : bgSprite)
        bg->SetPosition(0, 0);
}
void CreateSiroKuroStage(Sprite* _sprite){
    _sprite->Create(L"Resource/Scene/Game/Stage/SiroKuroStage.png");
    D3DXVECTOR2 pos(0, 0);
    _sprite->SetPosition(pos);
    //@ x 1366* y 768
    _sprite->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F size;
    size.height = 768.f;
    size.width = 1366.f;
    _sprite->SetSize(size);
    sprites.push_back(_sprite);

    //アニメーション用
    sprite_anime.reset(new Sprite);
    sprite_anime->Create(L"Resource/Scene/Game/Stage/SiroKuroStage.png");
    D3DXVECTOR2 animepos(0, 0);
    sprite_anime->SetPosition(animepos);
    //@ x 1366* y 768
    sprite_anime->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F anime_size;
    anime_size.height = 768.f;
    anime_size.width = 1366.f;
    sprite_anime->SetSize(anime_size);
    sprite_animes.push_back(sprite_anime);

    Sprite* sprite1 = new Sprite;
    sprite1->Create(L"Resource/Scene/Game/Stage/SiroKurobg1.png");
    bgSprite.push_back(sprite1);
    Sprite* sprite2 = new Sprite;
    sprite2->Create(L"Resource/Scene/Game/Stage/SiroKurobg2.png");
    bgSprite.push_back(sprite2);
    Sprite* sprite3 = new Sprite;
    sprite3->Create(L"Resource/Scene/Game/Stage/SiroKurobg3.png");
    bgSprite.push_back(sprite3);


    for (auto& bg : bgSprite)
        bg->SetPosition(0, 0);
}
void CreateYellowStage(Sprite* _sprite){
    _sprite->Create(L"Resource/Scene/Game/Stage/YellowStage.png");
    D3DXVECTOR2 pos(0, 0);
    _sprite->SetPosition(pos);
    //@ x 1366* y 768
    _sprite->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F size;
    size.height = 768.f;
    size.width = 1366.f;
    _sprite->SetSize(size);
    sprites.push_back(_sprite);

    //アニメーション用
    sprite_anime.reset(new Sprite);
    sprite_anime->Create(L"Resource/Scene/Game/Stage/YellowStage.png");
    D3DXVECTOR2 animepos(0, 0);
    sprite_anime->SetPosition(animepos);
    //@ x 1366* y 768
    sprite_anime->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F anime_size;
    anime_size.height = 768.f;
    anime_size.width = 1366.f;
    sprite_anime->SetSize(anime_size);
    sprite_animes.push_back(sprite_anime);

    Sprite* sprite1 = new Sprite;
    sprite1->Create(L"Resource/Scene/Game/Stage/Yellowbg1.png");
    bgSprite.push_back(sprite1);
    Sprite* sprite2 = new Sprite;
    sprite2->Create(L"Resource/Scene/Game/Stage/Yellowbg2.png");
    bgSprite.push_back(sprite2);
    Sprite* sprite3 = new Sprite;
    sprite3->Create(L"Resource/Scene/Game/Stage/Yellowbg3.png");
    bgSprite.push_back(sprite3);


    for (auto& bg : bgSprite)
        bg->SetPosition(0, 0);
}
void CreateNoCollarStage(Sprite* _sprite){
    _sprite->Create(L"Resource/Scene/Game/Stage/NoColorStage.png");
    D3DXVECTOR2 pos(0, 0);
    _sprite->SetPosition(pos);
    //@ x 1366* y 768
    _sprite->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F size;
    size.height = 768.f;
    size.width = 1366.f;
    _sprite->SetSize(size);
    sprites.push_back(_sprite);

    //アニメーション用
    sprite_anime.reset(new Sprite);
    sprite_anime->Create(L"Resource/Scene/Game/Stage/NoColorStage.png");
    D3DXVECTOR2 animepos(0, 0);
    sprite_anime->SetPosition(animepos);
    //@ x 1366* y 768
    sprite_anime->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F anime_size;
    anime_size.height = 768.f;
    anime_size.width = 1366.f;
    sprite_anime->SetSize(anime_size);
    sprite_animes.push_back(sprite_anime);

    Sprite* sprite1 = new Sprite;
    sprite1->Create(L"Resource/Scene/Game/Stage/NoColorbg1.png");
    bgSprite.push_back(sprite1);
    Sprite* sprite2 = new Sprite;
    sprite2->Create(L"Resource/Scene/Game/Stage/NoColorbg2.png");
    bgSprite.push_back(sprite2);
    Sprite* sprite3 = new Sprite;
    sprite3->Create(L"Resource/Scene/Game/Stage/NoColorbg3.png");
    bgSprite.push_back(sprite3);


    for (auto& bg : bgSprite)
        bg->SetPosition(0, 0);
}

void CreateEachStage(int stageLevel){
    /*

    int level;
    struct StageFixtures{
    float pos[2][8];
    int counter
    };

    std::list<StageFixture>& stageObjects = StageLoader::GetFixture();



    for (int i = 0; i < 100; ++i){
    b2PolygonShape polygon;
    polygon.Set(b2Vec2(pos[0][i],pos[1][i]);
    }
    */
    Special_BLUE.reset(new Sprite);
    Special_BLUE->Create(L"Resource/Scene/Game/Stage/blue_SSKILL.png");
    D3DXVECTOR2 BLUESKILLpos(0, 400);
    Special_BLUE->SetPosition(BLUESKILLpos);
    //@ x 1366* y 768
    Special_BLUE->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F BLUESKILL_size;
    BLUESKILL_size.height = 768.f;
    BLUESKILL_size.width = 1366.f;
    Special_BLUE->SetSize(BLUESKILL_size);
    Special_SKILLs.push_back(Special_BLUE);

    Special_RED.reset(new Sprite);
    Special_RED->Create(L"Resource/Scene/Game/Stage/red_SSKILL.png");
    D3DXVECTOR2 REDSKILLpos(0, 400);
    Special_RED->SetPosition(REDSKILLpos);
    //@ x 1366* y 768
    Special_RED->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F REDSKILL_size;
    REDSKILL_size.height = 768.f;
    REDSKILL_size.width = 1366.f;
    Special_RED->SetSize(REDSKILL_size);
    Special_SKILLs.push_back(Special_RED);

    Special_YELLOW.reset(new Sprite);
    Special_YELLOW->Create(L"Resource/Scene/Game/Stage/yellow_SSKILL.png");
    D3DXVECTOR2 YELLOWSKILLpos(0, 400);
    Special_YELLOW->SetPosition(YELLOWSKILLpos);
    //@ x 1366* y 768
    Special_YELLOW->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F YELLOWSKILL_size;
    YELLOWSKILL_size.height = 768.f;
    YELLOWSKILL_size.width = 1366.f;
    Special_YELLOW->SetSize(YELLOWSKILL_size);
    Special_SKILLs.push_back(Special_YELLOW);

    Special_SIROKURO.reset(new Sprite);
    Special_SIROKURO->Create(L"Resource/Scene/Game/Stage/sirokuro_SSKILL.png");
    D3DXVECTOR2 SIROKUROSKILLpos(0, 400);
    Special_SIROKURO->SetPosition(SIROKUROSKILLpos);
    //@ x 1366* y 768
    Special_SIROKURO->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F SIROKUROSKILL_size;
    SIROKUROSKILL_size.height = 768.f;
    SIROKUROSKILL_size.width = 1366.f;
    Special_SIROKURO->SetSize(SIROKUROSKILL_size);
    Special_SKILLs.push_back(Special_SIROKURO);

    //スペシャルスキルのBGM系
    RedSkillSE = Sound::CreateSE("Resource/Voice/chara1_gd.wav");
    BlueSkillSE = Sound::CreateSE("Resource/Voice/chara2_gd.wav");
    YellowSkillSE = Sound::CreateSE("Resource/Voice/chara3_gd.wav");
    SiroKuroSkillSE = Sound::CreateSE("Resource/Voice/chara4_gd.wav");

    Sprite* sprite = new Sprite;
    switch (StageID)
    {
        //赤（キツネ）
    case 0:
        CreateRedStage(sprite);
        break;
       //青（男）
    case 1:
        CreateBlueStage(sprite);
        break;
        //白黒（女）
    case 2:
        CreateSiroKuroStage(sprite);
        break;
        //黄色（女の子）
    case 3:
        CreateYellowStage(sprite);
        //test = 0;
        break;
        //無色
    case 4:
		CreateNoCollarStage ( sprite );
        break;
        //やり方
    default:
        CreateNoCollarStage(sprite);
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

void Stage::StageDamage ( float _damage, int _playernum ){
    HP = HP - _damage;
    playernum = _playernum;
}
void SetStageHP(float _HP){
    HP = _HP;
}

void Stage::CriateStage(){
    Stageflg = false;
    counter = 0;
    //            D3DXVECTOR2 pos(0, 580);
    //            sprite_anime->SetPosition(pos);
    //@ x 1366* y 768
    sprite_anime->SetTrimming(0, 0, 1366, 768);
    D2D1_SIZE_F size;
    size.height = 768.f;
    size.width = 1366.f;
    sprite_anime->SetSize(size);
    HP = 500.f + rand() % 500;
    switch (Charatype)
    {
    case 0://赤
        Special_RED->SetPosition(D3DXVECTOR2(0, 400));
        break;
    case 1://あお
        Special_BLUE->SetPosition(D3DXVECTOR2(0, 400));
        break;
    case 2://き
        Special_YELLOW->SetPosition(D3DXVECTOR2(0, 400));
        break;
    case 3://しろくろ
        Special_SIROKURO->SetPosition(D3DXVECTOR2(0, 400));
        break;
    }
    CreateWorldEdge();

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

void Stage::SetSkillEnd(bool isbool){
    
    SkillEnd = isbool;
    fade->SetAlpha(0);
    Suppressioncount = 1;
    isSuppression = true;
    switch (Charatype)
    {
    case 0:
        Suppression_fade.reset(new Fade(L"Resource/Scene/Game/Stage/red_Suppression.png"));
        Suppression_fade->SetAlpha(Suppressioncount);
        break;
    case 1:
        Suppression_fade.reset(new Fade(L"Resource/Scene/Game/Stage/blue_Suppression.png"));
        Suppression_fade->SetAlpha(Suppressioncount);
        break;
    case 2:
        Suppression_fade.reset(new Fade(L"Resource/Scene/Game/Stage/yellow_Suppression.png"));
        Suppression_fade->SetAlpha(Suppressioncount);
        break;
    case 3:
        Suppression_fade.reset(new Fade(L"Resource/Scene/Game/Stage/sirokuro_Suppression.png"));
        Suppression_fade->SetAlpha(Suppressioncount);
        break;
    }
    SuppressionScale = 2;

}
/*
この後はコリジョンを外して入れるだけ
*/

void Stage::DettachFixture(){
    b2Fixture* fixture = breakableStage->GetFixtureList();
    if (fixture == nullptr){
        return;
    }

    while (fixture != nullptr){
        b2Fixture* temp = fixture->GetNext();
        breakableStage->DestroyFixture(fixture);
        fixture = temp;
    }
}



void Stage::FadeDraw(){
    fade->Draw();
    if (isSuppression == true){
        Suppressioncount -= 0.005f;
        if (Suppressioncount <= 0)
            isSuppression = false;
        if (Suppressioncount >= 0.8f){
            if(isSuppressionScale == false)
                SuppressionScale -= 0.08;
            if (SuppressionScale <= 0.8){
                if (isPlaySE(Charatype))
                    Stage::PlaySpecialSkillSE(Charatype);
                isSuppressionScale = true;
            }

            Suppression_fade->SetScale(SuppressionScale);
        }
        if (Suppressioncount <= 0.5f){
            //後で声入れる
            isSuppressionScale = false;
            Suppression_fade->AddAlpha(-0.01f);
            if (Suppressioncount <= 0){
            }
        }
        Suppression_fade->Draw();
        
    }
}

void Stage::SetStagenum(int _ID){
    StageID = _ID;
}

void Stage::SetCharaType(int _type){
    Charatype = _type;
}

int Stage::GetStageNum(){
    return StageID;
}

void Stage::PlaySpecialSkillSE(int _playertype){
    switch (_playertype)
    {
    case 0:
        RedSkillSE->Play();
        break;
    case 1:
        BlueSkillSE->Play();
        break;
    case 2:
        YellowSkillSE->Play();
        break;
    case 3:
        SiroKuroSkillSE->Play();
        break;
    }
}

bool Stage::isPlaySE(int _playertype){
    switch (_playertype)
    {
    case 0:
        if (RedSkillSE->GetPlayingTime() > 0)
            return true;
        else
            return false;
        break;
    case 1:
        if (BlueSkillSE->GetPlayingTime() > 0)
            return true;
        else
            return false;
        break;
    case 2:
        if (YellowSkillSE->GetPlayingTime() > 0)
            return true;
        else
            return false;
        break;
    case 3:
        if (SiroKuroSkillSE->GetPlayingTime() > 0)
            return true;
        else
            return false;
        break;
    }
}

D3DXVECTOR2 Stage::GetSpecialSkillpos(int _playertype){
    switch (_playertype)
    {
    case 0:
        return Special_RED->GetPosition();
        break;
    case 1:
        return Special_BLUE->GetPosition();
        break;
    case 2:
        return Special_YELLOW->GetPosition();
        break;
    case 3:
        return Special_SIROKURO->GetPosition();
        break;
    }
}
void Stage::SetSpecialSkill(int _playertype, int pos){
    switch (_playertype)
    {
    case 0:
        Special_RED->SetPositionY(pos);
        break;
    case 1:
        Special_BLUE->SetPositionY(pos);
        break;
    case 2:
        Special_YELLOW->SetPositionY(pos);
        break;
    case 3:
        Special_SIROKURO->SetPositionY(pos);
        break;
    }
}

void Stage::StageDraw(int _playernum){
    switch (_playernum)
    {
    case 0:
        Special_RED->Draw();
        break;
    case 1:
        Special_BLUE->Draw();
        break;
    case 2:
        Special_YELLOW->Draw();
        break;
    case 3:
        Special_SIROKURO->Draw();
        break;
    }
}