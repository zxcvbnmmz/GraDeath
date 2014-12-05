#include "System/Window.h"

using namespace System;

Window::WindowData Window::windowData;

bool Window::Create(WNDPROC proc, HINSTANCE inst){
	if (windowData.hwnd){
		return true;
	}

	LPCWSTR fileName = L"Profile/Profile.ini";

	int x = GetPrivateProfileInt(L"WindowInfo", L"WindowPosX", 0, fileName);
	int y = GetPrivateProfileInt(L"WindowInfo", L"WindowPosY", 0, fileName);
	windowData.width = GetPrivateProfileInt(L"WindowInfo", L"WindowWidth", 640, fileName);
	windowData.height = GetPrivateProfileInt(L"WindowInfo", L"WindowHeight", 480, fileName);

	WCHAR windowName[256], fullScreen[8], iconName[256];
	GetPrivateProfileString(L"WindowInfo", L"WindowName", L"", windowName, wcslen(windowName), fileName);
	GetPrivateProfileString(L"WindowInfo", L"FullScreen", L"", fullScreen, wcslen(fullScreen), fileName);
	GetPrivateProfileString(L"WindowInfo", L"Icon", IDI_APPLICATION, iconName, wcslen(iconName), fileName);

	WNDCLASSEX wc = { sizeof(wc), CS_HREDRAW | CS_VREDRAW, proc, 0, 0, inst, LoadIcon(NULL, iconName), LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(LTGRAY_BRUSH), L"", windowName, LoadIcon(NULL, IDI_APPLICATION) };
	RegisterClassEx(&wc);

	if (wcscmp(fullScreen, L"true") == 0){
		SetWindowLong(windowData.hwnd, GWL_STYLE, WS_VISIBLE | WS_POPUP);
		DEVMODE devMode;
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
		devMode.dmPelsWidth = windowData.width;
		devMode.dmPelsHeight = windowData.height;

		RECT rc;
		SetRect(&rc, 0, 0, windowData.width, windowData.height);
		AdjustWindowRectEx(&rc, WS_POPUP, FALSE, WS_EX_TOPMOST);
		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
		windowData.hwnd = CreateWindowEx(WS_EX_TOPMOST, windowName, windowName, WS_POPUP, 0, 0, windowData.width, windowData.height, 0, 0, inst, 0);
	}
	else{
		windowData.hwnd = CreateWindow(windowName, windowName, WS_OVERLAPPEDWINDOW, x, y, windowData.width, windowData.height, 0, 0, inst, 0);
	}

	if (!windowData.hwnd){
		return FALSE;
	}


#ifdef _DEBUG
	int resizeX = GetPrivateProfileInt(L"WindowInfo", L"WindowResizedWidth", 0, fileName);
	int resizeY = GetPrivateProfileInt(L"WindowInfo", L"WindowResizedHeight", 0, fileName);
	MoveWindow(windowData.hwnd, x, y, resizeX, resizeY, false);
#endif

	ShowWindow(windowData.hwnd, SW_SHOW);
	UpdateWindow(windowData.hwnd);

	return true;
}
