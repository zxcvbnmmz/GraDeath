#ifndef _SCREEN_SHOT_H__
#define _SCREEN_SHOT_H__

#include <D3D10_1.h>

namespace Utility{
	namespace{
		const static int MAX_SCREEN_SHOT = 999;
	}
	bool CreateScreenShot(LPCWSTR filePath, unsigned int maxFileIndex = MAX_SCREEN_SHOT);
	bool CreateScreenShot(LPCWSTR filePath, LPCWSTR fileHedderName, unsigned int maxFileIndex = MAX_SCREEN_SHOT);
}

#endif	// end of ScreenShot