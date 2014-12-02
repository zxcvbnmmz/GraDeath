#ifndef _RESULT_SCENE_H__
#define _RESULT_SCENE_H__

#include "Scene.h"
#include "D2D/Sprite/Sprite.h"

class ResultScene : public Scene{
public:
	ResultScene();

	SCENE_STATUS Execute();
	void Draw();

private:
	Sprite s1st, s2nd, s3rd, s4th;
	D3DXVECTOR2 pos_1st, pos_2nd, pos_3rd, pos_4th;
};


#endif	// end of ResulScene