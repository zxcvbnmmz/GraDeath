#include "System/System.h"
#include "System/D3DCore.h"
#include "System/D2DCore.h"
#include "Sound/Sound.h"
#include <System\Window.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

namespace System{
	namespace{
		void* mutex;
	}

	bool Initialize(HINSTANCE hInstance){
		mutex = CreateMutex(NULL, true, L"Library");
		if (GetLastError() == ERROR_ALREADY_EXISTS){
			MessageBox(NULL, L"多重起動してるよ", L"エラー", MB_OK);
			return FALSE;
		}
		Window::Create(WndProc, hInstance);

		int width, height;
		Window::GetWindowSize(&width, &height);
		HWND hwnd;
		Window::GetHWND(&hwnd);

		CoInitialize(NULL);
		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		if (FAILED(D3DCore::Init(hwnd, width, height)))return FALSE;
		if (FAILED(D2DCore::Init()))return FALSE;

		if (!Sound::Initialize()){
			return false;
		}

		return TRUE;
	}

	bool Loop(){
		static MSG msg = { 0 };
		while (msg.message != WM_QUIT){
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				Sleep(1);
				return TRUE;
			}
		}
		return FALSE;
	}

	void Release(){
		Sound::Release();

		D2DCore::Destroy();
		D3DCore::Destroy();

		CloseHandle(mutex);
	}

	LRESULT MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
		switch (iMsg){
		case WM_KEYDOWN:
			switch ((char)wParam){
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_SIZE:
			//RECT rect;
			//::GetClientRect(hwnd, &rect);
			break;
		case WM_PAINT:
			break;

		case WM_ERASEBKGND:
			HWND hwnd;
			Window::GetHWND(&hwnd);
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		default:
			break;
		}
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}

};

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	return System::MsgProc(hWnd, uMsg, wParam, lParam);
}
