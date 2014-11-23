#ifndef _STAGE_ICON_H_
#define _STAGE_ICON_H_

#include <memory>
#include "D2D/Sprite/Sprite.h"
#include "CharacterController/CharacterInfo.h"


class StageIcon
{
private:
	int stageNum = 0;

	Sprite iconSprite[ 6 ];
	Sprite selectSprite;

public:
	StageIcon ();

	~StageIcon ();

	void SetUp ();

	void Update ();

	void Draw ();

	int GetStageNum ();

private:
	void CursorMovw ();

};


#endif