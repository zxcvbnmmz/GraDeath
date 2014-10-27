#include "Object/Menu.h"
#include "Utility/Converter.h"
#include <assert.h>
#include <stdarg.h>
#include "Input/GamePad.h"

Menu::Menu():cursor(0){

}

Menu::~Menu(){
}

bool Menu::Create(MenuInfo* _menu, ...){
	assert(_menu != nullptr);

	va_list args;
	va_start(args, _menu);

	std::shared_ptr<MenuObject> menu(new MenuObject(_menu));
	menues.push_back(menu);

	while(true){
		MenuInfo* info = va_arg(args, MenuInfo*);
		if (info == nullptr){
			break;
		}
		menu.reset(new MenuObject(info));
		menues.push_back(menu);
	}

	va_end(args);

	return true;
}

std::shared_ptr<Menu::MenuObject> Menu::operator[](int index){
	return menues[index];
}

void Menu::Select(unsigned int index){
	menues[index]->type = MenuObject::SELECTED;
}

void Menu::Unselect(unsigned int index){
	menues[index]->type = MenuObject::NORMAL;
}

void Menu::UpdateByInput(){
	if (GamePad::getAnyGamePadPressed(BUTTON_DOWN)){
		Unselect(cursor);
		cursor = (cursor + 1) % menues.size();
		Select(cursor);
	}
	else if (GamePad::getAnyGamePadPressed(BUTTON_UP)){
		Unselect(cursor);
		cursor = (cursor + menues.size() - 1) % menues.size();
		Select(cursor);
	}

}

void Menu::Draw(){
	for (std::shared_ptr<MenuObject> _menu : menues){
		_menu->sprite[_menu->type].Draw();
	}
}



