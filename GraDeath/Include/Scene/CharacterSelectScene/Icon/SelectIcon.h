#ifndef _SELECT_ICON_H_
#define _SELECT_ICON_H_

#include <memory>
#include "D2D/Sprite/Sprite.h"
#include "CharacterController/CharacterInfo.h"


class SelectIcon
{
private:
	struct IconState;
	IconState* iconState;

	Sprite iconSprite;
	Sprite charSprite[ 5 ];
	Sprite selectSprite[ 5 ];

public:
	SelectIcon ();

	~SelectIcon ();

	void SetUp ();

	void Draw ();

	bool CursorCollision ( int, D3DXVECTOR2& );

	CharacterInfo GetCharacterInfo ( int );

	void SetRandomChar ( int _num, CharacterInfo::PLAYER_TYPE _type );

	bool GethitFlg ( int _num );

};


#endif