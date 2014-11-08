#include "Stage/Stage.h"
#include "World/World.h"
#include "System/Window.h"
#include <Box2D\Box2D.h>
#include "D2D/Sprite/Sprite.h"
#include <vector>
#include <algorithm>
#include <functional>

namespace{
	const static float PTM_RATIO = 32.0f;
	std::vector<Sprite*> sprites;
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
	std::for_each(sprites[0], sprites[sprites.size()-1], std::bind2nd(std::mem_fun_ref(&Sprite::Draw),DRAW_NORMAL));
}

void Stage::Release(){
	World::DestoryBody(screenEdgeBody);
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

	// ���
	screenEdgeShape.Set(upperLeftCorner, upperRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density);
	// ����
	screenEdgeShape.Set(lowerLeftCorner, lowerRightCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density);
	// ����
	screenEdgeShape.Set(upperLeftCorner, lowerLeftCorner);
	screenEdgeBody->CreateFixture(&screenEdgeShape, density);
	// �E��
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

	int spriteNum = 0;

	for (int i = 0; i < spriteNum; ++i){
		Sprite* sprite;
		/*�e��p�����[�^�̐ݒ�*/

		sprites.push_back(sprite);
	}
}




