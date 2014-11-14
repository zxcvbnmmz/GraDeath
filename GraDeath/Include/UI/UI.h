#ifndef _UI_H__
#define _UI_H__

#include "D2D/Sprite/Sprite.h"
#include <vector>
#include <memory>

struct UIData;
typedef std::shared_ptr<UIData> UI;

namespace UIManager{
	void Release();
	UI Create(int size, int priority = 0);
}

struct UIData{
	friend class UICreator;
	friend class shared_ptr;
public:
	~UIData();
	std::vector<class Sprite*> sprite;
	unsigned int priority;

private:
	UIData(){}
	UIData(const UIData&);
	UIData& operator=(const UIData&);
};


#endif	// end of UI

