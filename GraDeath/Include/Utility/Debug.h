#ifndef _DEBUG_H__
#define _DEBUG_H__

#include <Windows.h>

#define DebugAssert(boolean, text) OutputError(boolean, text, __FILE__, __LINE__);

bool DebugPrint(const char *str, ...);
void OutputError(bool b, LPCWSTR text, const char* file, int line);

#endif	// end of Debug