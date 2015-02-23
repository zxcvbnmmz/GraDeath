#ifndef _SELECT_CURSOR_H_
#define _SELECT_CURSOR_H_

#include <memory>

#include "D2D/Sprite/Sprite.h"
#include "CharacterController/CharacterInfo.h"

#ifdef _DEBUG
#include "D2D/Text/TextObject.h"
#endif

struct D3DXVECTOR2;
struct CursorState;
class SelectIcon;

class SelectCursor
{
private:
	CursorState* cursorState;
	std::shared_ptr<SelectIcon> icon;
	int maxWidth = 0, maxHeight = 0;

#ifdef _DEBUG
	D2D::TextObject temp;
	int tempCharNum = 0; 
#endif

public:
	SelectCursor ();

	~SelectCursor ();

	void SetUp ();

	void Update ();

	void Draw ();

	bool AllSelectCheck ();

	bool GetPadCursorPositon ( int, D3DXVECTOR2& );

	CharacterInfo GetCharacterInfo ( int );

private:
	void SubUpdate ( int );

	void Move ( int );

	void Determination ( int  );

};


#endif