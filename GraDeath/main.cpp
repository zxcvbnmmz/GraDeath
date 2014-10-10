#include <Windows.h>
#include <crtdbg.h>
#include <Box2D\Box2D.h>
#include "System/System.h"
#include "Graphic/Graphic.h"

INT WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR, INT){
#ifdef _DEBUG
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif

	if (!System::Initialize(inst)){
		return 0;
	}

	while (System::Loop()){
		Graphic::Clear();

		Graphic::Present(0, 0);
	}

	System::Release();

	return 1;
}