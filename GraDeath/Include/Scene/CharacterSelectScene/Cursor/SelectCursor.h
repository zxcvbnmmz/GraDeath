#ifndef _SELECT_CURSOR_H_
#define _SELECT_CURSOR_H_

#include <memory>

#include "D2D/Sprite/Sprite.h"


struct D3DXVECTOR2;
struct CursorState;


class SelectCursor
{
private:
	CursorState* cursorState;

public:
	SelectCursor ();

	~SelectCursor ();

	void SetUp ();

	void Update ();

	void Draw ();

	bool AllSelectCheck ();

	bool GetPadCursorPositon ( int, D3DXVECTOR2& );

private:
	void SubUpdate ( int );

	void Move ( int );

	void Determination ( int  );

};


#endif