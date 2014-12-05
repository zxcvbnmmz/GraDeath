#ifndef _TITLE_SCENE_H__
#define _TITLE_SCENE_H__

#include "Scene.h"
#include "D2D/Sprite/Sprite.h"

#include "D2D/Text/TextObject.h"

class TitleScene : public Scene{
public:
	TitleScene();
	~TitleScene();

	SCENE_STATUS Execute();    
	void Draw();

private:
	int ExecuteFadeOut(){ return 2; }
	Sprite sprite, sStart, sCredit, sExit, sVector;
	D3DXVECTOR2 start_pos, credit_pos, exit_pos, vect_pos, select_pos;
	int tCount, select_i;

	D2D::TextObject t;
};

#endif	// end of TitleScene