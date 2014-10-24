#ifndef _TITLE_SCENE_H__
#define _TITLE_SCENE_H__

#include "Scene.h"
#include <memory>

class CwnSkinMesh;
class BoneAnimeData;
class Shader;

class TitleScene : public Scene{
public:
	TitleScene();

	SCENE_STATUS Execute();
	void Draw();

private:

	std::shared_ptr< CwnSkinMesh > testModel;
	std::shared_ptr< BoneAnimeData > testAnime;

};

#endif	// end of TitleScene