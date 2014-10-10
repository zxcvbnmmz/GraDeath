#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include <stack>
#include <queue>
#include "Scene/Factory/TitleFactory.h"
#include "Scene/SceneFactory.h"

namespace{
	std::stack<Scene*> scenes;
	std::queue<Scene*> reserve;
}

bool SceneManager::Initialize(){
	TitleFactory tf;
	SceneFactory::Stack(&tf);
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
	return 1;
}

void SceneManager::Draw(){

	scenes.top()->Draw();

}

void SceneManager::Stack(Scene* _scene){
	if(!scenes.empty())
		scenes.top()->OnStack();
	scenes.push(_scene);
}

void SceneManager::Reserve(Scene* _scene){
	reserve.push(_scene);
}
