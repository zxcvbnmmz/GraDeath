#ifndef _SELECT_CURSOR_H_
#define _SELECT_CURSOR_H_

#include <memory>


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

	D3DXVECTOR2& GetPadCursorPositon ( int num );

};


#endif