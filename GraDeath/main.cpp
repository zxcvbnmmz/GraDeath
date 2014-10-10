#include <crtdbg.h>
#include "System/System.h"
#include "Graphic/Graphic.h"
#include "Scene/SceneManager.h"

INT WINAPI WinMain(HINSTANCE inst, HINSTANCE, LPSTR, INT){
#ifdef _DEBUG
	::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif

	if (!System::Initialize(inst)){
		return 0;
	}

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