#ifndef _TITLE_SCENE_H__
#define _TITLE_SCENE_H__

#include "Scene.h"
#include <memory>

class CwnStaticMesh;
class Shader;
class TestCamera;

class TitleScene : public Scene{
public:
	TitleScene();

	SCENE_STATUS Execute();
	void Draw();

private:

	std::shared_ptr< CwnStaticMesh > testModel;
	std::shared_ptr< TestCamera > testCamera;

};

#endif	// end of TitleScene