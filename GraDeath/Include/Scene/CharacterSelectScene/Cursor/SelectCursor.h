#ifndef _SELECT_CURSOR_H_
#define _SELECT_CURSOR_H_

#include <memory>
#include "D2D/Sprite/Sprite.h"


struct CursorState;
class SelectCursor
{
private:
	CursorState* cursorState;

public:
	SelectCursor ();

	~SelectCursor ();

	void SetUp ();

	void Draw ();

	D3DXVECTOR2& GetPadCursorPositon ( int num );

};


#endif