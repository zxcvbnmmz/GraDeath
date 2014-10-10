#ifndef _WINDOW_H__
#define _WINDOW_H__

#include <Windows.h>
#include <memory>

namespace System{
	class Window{
	public:
		static bool Create(WNDPROC proc, HINSTANCE inst);
		static void GetHWND(HWND* _hwnd);
		static void GetWindowSize(int* _width, int* _height);

	private:
		Window();
		Window(const Window&);
		Window& operator=(const Window&);

		static struct WindowData{
			HWND hwnd;
			int width;
			int height;
		}windowData;
	};

	inline void Window::GetHWND(HWND* _hwnd){
		*_hwnd = windowData.hwnd;
	}

	inline void Window::GetWindowSize(int* _width, int* _height){
		*_width = windowData.width;
		*_height = windowData.height;
	}


}

#endif	// end of Window