#include "UI/UIManager.h"
#include "UI/UI.h"
#include "D2D/Sprite/Sprite.h"
#include <vector>
#include <algorithm>

namespace {
	std::vector<UI> UIs;
};

UIData::~UIData(){
	std::for_each(sprite.begin(), sprite.end(), [=](Sprite* _sprite){
		if (_sprite != nullptr){
			delete _sprite;
			_sprite = nullptr;
		}
	});
	sprite.clear();
}

class UICreator{
public:
	static UI Create(int size, int priority){
		std::shared_ptr<UIData> newUI;
		newUI.reset(new UIData);

		newUI->priority = priority;
		
		if (UIs.empty()){
			UIs.insert(UIs.begin(), newUI);
			return newUI;
		}

		std::vector<UI>::iterator it = UIs.begin();
		for (; it != UIs.end(); ++it){
			if ((*it)->priority > newUI->priority){
				UIs.insert((it), newUI);
				return newUI;
			}
		}

		UIs.insert(UIs.end(), newUI);
		return newUI;
	}
};

void UIManager::Draw(){
	/*for (UI ui : UIs){
		for (Sprite* sprite : ui->sprite){
			sprite->Draw();
		}
	}*/
}

UI UIManager::Create(int size, int priority){
	return UICreator::Create(size, priority);
}

void UIManager::Release(){
	std::for_each(UIs.begin(), UIs.end(), [=](UI ui){
		ui.reset();
	});
	UIs.clear();
}



