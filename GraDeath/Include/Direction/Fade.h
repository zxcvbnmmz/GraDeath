#ifndef _FADE_H__
#define _FADE_H__

#include <D3D10_1.h>
#include "Direction.h"

enum FADE_STATUS{
	FADE_UNCLEAR,
	FADE_CLEAR,
	FADE_HALF_CLEAR,
};

class Fade : public Direction{
public:
	Fade(LPCWSTR fileName = L"Resource/UI/Game/skill_mask.png");
	~Fade();

	FADE_STATUS AddAlpha(float _alpha);
	void SetAlpha(float _alpha);
	void Draw();
	void SetScale(float scale);
	void SetPosition(int x, int y);

	CREATE(Fade);

private:
	float alpha = 0;
};

#endif	// end of Fade