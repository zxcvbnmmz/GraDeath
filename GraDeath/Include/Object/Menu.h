#ifndef _MENU_OBJECT_H__
#define _MENU_OBJECT_H__

#include <vector>
#include <memory>
#include "D2D/Sprite/Sprite.h"

struct MenuInfo{
	float x;
	float y;
	LPWSTR fileName;
	LPWSTR selectedFileName;

	MenuInfo():x(0), y(0){}
};

class Menu{
public:
	struct MenuObject{
		enum DRAW_TYPE{
			NORMAL,
			SELECTED
		}type;
		float x, y;
		Sprite sprite[2];
		MenuObject(MenuInfo* info) :x(info->x), y(info->y){
			sprite[NORMAL].Create(info->fileName);
			sprite[SELECTED].Create(info->selectedFileName);
		}
	};

	Menu();
	virtual ~Menu();
	bool Create(MenuInfo* menu, ...);
	std::shared_ptr<MenuObject> operator[](int index);
	void Select(unsigned int _pressed);
	void Unselect(unsigned int _pressed);
	int GetSelectedIndex();
	void UpdateByInput();
	void Active(bool _active);
	void Draw();
	

private:
	std::vector<std::shared_ptr<MenuObject>> menues;
	bool active;
	unsigned int cursor;
};

inline void Menu::Active(bool _active){
	active = _active;
}


#endif	// end of Menu