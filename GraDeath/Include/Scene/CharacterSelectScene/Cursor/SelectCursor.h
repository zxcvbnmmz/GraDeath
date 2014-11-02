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
	Sprite cursorIcon[ 4 ];

public:
	SelectCursor ();

	~SelectCursor ();

	void SetUp ();

	void Update ();

	void Draw ();

	D3DXVECTOR2& GetPadCursorPositon ( int num );

};


#endif