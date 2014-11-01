#include "Scene/CharacterSelectScene/Cursor/SelectCursor.h"
#include "Utility/SafeDelete.h"
#include "Input/GamePad.h"
#include "D2D/Sprite/Sprite.h"

struct CursorState
{
	Sprite cursor;
	D3DXVECTOR2 pos;
};

wchar_t* cursorName[] =
{
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_1.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_2.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_3.png",
	L"Resource/Scene/CharacterSelect/CharacterSelect_PlayerIcon_4.png"
};

D3DXVECTOR2 cursorPos[] =
{
	D3DXVECTOR2(50, 100),
	D3DXVECTOR2(870, 100),
	D3DXVECTOR2(50, 450),
	D3DXVECTOR2(870, 450),
};


SelectCursor::SelectCursor()
{
	cursorState = new CursorState[4];
}

SelectCursor::~SelectCursor()
{
	Util::safeDeleteArray(cursorState);
}

void SelectCursor::SetUp()
{
	
}

void SelectCursor::Update()
{

}

void SelectCursor::Draw()
{
	
}

D3DXVECTOR2& SelectCursor::GetPadCursorPositon(int num)
{
	return cursorState[num].pos;
}