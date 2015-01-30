#include "Utility/Debug.h"
#ifdef _DEBUG
#include "Utility/Converter.h"
#include <windows.h>
#include <iostream>
#endif

namespace Utility{

	bool DebugPrint(const char *str, ...){
#ifdef _DEBUG
		char debugOutBuff[128];

		va_list ap;
		va_start(ap, str);

		if (!vsprintf_s(debugOutBuff, 128, str, ap)){
			OutputDebugStringA("dprintf error.");
			return false;
		}

		OutputDebugStringA(debugOutBuff);

#endif
		return true;
	}

	void OutputError(bool _b, LPCWSTR _text, const char* _file, int _line){
#ifdef _DEBUG
		if (_b == false){
			WCHAR fileName[64], str[256];
			char file[64], ext[8];
			_splitpath_s(_file, nullptr, 0, nullptr, 0, file, 64, ext, 8);
			strcat_s(file, ext);
			Utility::ConvertToWChar(fileName, file);

			wsprintf(str, L"%s:%dçsñ⁄Ç©ÇÁÇÃÉGÉâÅ[      ", fileName, _line);
			MessageBox(NULL, _text, str, MB_OK);
		}
#endif
	}

}
