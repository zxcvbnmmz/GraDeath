#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include <stack>
#include "Scene/Factory/TitleFactory.h"
#include "Scene/SceneFactory.h"
#include "Graphic/Graphic.h"
#include "World/World.h"

#include "Input/InputManager.h"
#include "UI/UIManager.h"
#include "Utility/FPS.h"
#include "Pool/ObjectPool.h"

namespace{
	std::stack<Scene*> scenes;
	Scene* reserve;

	FPS fps;
}

bool SceneManager::Initialize(){
	//InputManager::Initialize();
	
	//TitleFactory tf;
	//SceneFactory::Stack(&tf);
	//Graphic::SetClearColor ( 0, 0, 1, 1 );

	fps.SetFPS(60);

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

	if (reserve != nullptr){
		delete reserve;
		reserve = nullptr;
	}

	ObjectPoolManager::Destroy();
}

int SceneManager::Execute(){
	if(scenes.empty()){
		return 0;
	}

	InputManager::Update();

	Scene* currentScene = scenes.top();

	int ret = currentScene->Execute();

	if(ret == END_PROCESS){
		delete currentScene;
		currentScene = nullptr;
		scenes.pop();

		if(reserve){
			scenes.push(reserve);
			reserve = nullptr;
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
	UIManager::Draw();

#ifdef _DEBUG
	World::DrawDebugData();
#endif

	Graphic::D2D::EndDraw();
	Graphic::Present ( 0, 0 );

	fps.WaitFrame();
}

void SceneManager::Stack(Scene* _scene){
	if(!scenes.empty())
		scenes.top()->OnStack();
	scenes.push(_scene);
}

void SceneManager::Reserve(Scene* _scene){
	if(reserve == nullptr)
		reserve = _scene;
}
