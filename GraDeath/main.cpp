#ifdef _MSC_VER
#	define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
#	define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT 1
#endif

#include <crtdbg.h>
#include "System/System.h"
#include "Graphic/Graphic.h"
#include "Scene/SceneManager.h"

#ifdef _DEBUG
#include "Utility/Debug.h"
#include <System/Window.h>
#endif

INT WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR, INT){
#ifdef _DEBUG
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
	
	if (!System::Initialize(inst)){
		return 0;
	}

#ifdef _DEBUG
	HWND hwnd;
	System::Window::GetHWND(&hwnd);
	int w, h;
	System::Window::GetWindowSize(&w,&h);
	MoveWindow(hwnd, 0, 0, w/1.3f, h/1.3f, false);
#endif

	SceneManager::Initialize();

	while (System::Loop()){
		Graphic::Clear();

		if (!SceneManager::Execute()){
			break;
		}

		Graphic::Present(0, 0);
	}

	SceneManager::Release();

	System::Release();

	return 1;
}