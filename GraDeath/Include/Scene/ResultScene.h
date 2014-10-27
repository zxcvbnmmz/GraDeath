#ifndef _RESULT_SCENE_H__
#define _RESULT_SCENE_H__

#include "Scene.h"

class ResultScene : public Scene{
public:
	ResultScene();

	SCENE_STATUS Execute();
	void Draw();

private:
};


#endif	// end of ResulScene