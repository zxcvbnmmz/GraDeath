#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include <stack>
#include <queue>
#include "Scene/Factory/TitleFactory.h"
#include "Scene/SceneFactory.h"
#include "Graphic/Graphic.h"
#include "World/World.h"

#include "Input/Gamepad.h"
#include "Input/Keyboard.h"

namespace{
	std::stack<Scene*> scenes;
	std::queue<Scene*> reserve;
}

bool SceneManager::Initialize(){
	GamePad::init();
	
	TitleFactory tf;
	SceneFactory::Stack(&tf);
	Graphic::SetClearColor ( 0, 0, 1, 1 );
	return true;
}

void SceneManager::Release(){
	Scene* tempScene;
	while(!scenes.empty()){
		tempScene = scenes.top();
		delete tempScene;
		tempScene = nullptr;
		scenes.pop();
	}

	while(!reserve.empty()){
		tempScene = reserve.front();
		delete tempScene;
		tempScene = nullptr;
		reserve.pop();
	}
}

int SceneManager::Execute(){
	if(scenes.empty()){
		return 0;
	}

	GamePad::update();
	Keyboard::Update();

	Scene* currentScene = scenes.top();

	int ret = currentScene->Execute();

	if(ret == END_PROCESS){
		delete currentScene;
		currentScene = nullptr;
		scenes.pop();

		if(!reserve.empty()){
			scenes.push(reserve.front());
			reserve.pop();
		}
	}else{
		Draw();
	}

	World::Step();

	return 1;
}

void SceneManager::Draw(){
	Graphic::Clear ();
	Graphic::D2D::BeginDraw();

	scenes.top()->Draw();

	Graphic::D2D::EndDraw();
	Graphic::Present ( 0, 0 );
}

void SceneManager::Stack(Scene* _scene){
	if(!scenes.empty())
		scenes.top()->OnStack();
	scenes.push(_scene);
}

void SceneManager::Reserve(Scene* _scene){
	reserve.push(_scene);
}
