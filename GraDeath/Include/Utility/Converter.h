#ifndef _CONVERTER_H__
#define _CONVERTER_H__

#include <D3DX10.h>

namespace Utility{
	extern const char* ConvertToChar(char* dst, LPCWSTR src);
	extern LPCWSTR ConvertToWChar(LPWSTR dst, const char* src);
	extern const char* ConvertToSJis(char* dst, LPWSTR byteArray);
	extern LPWSTR ConvertToUTF_16(LPWSTR dst, const char* src);
	extern D3DXMATRIX* ConvertToMatrix(D3DXMATRIX* dst, D3DXQUATERNION* src);
	extern D3DXQUATERNION* ConvertToQuaternion(D3DXQUATERNION* dst, D3DXMATRIX* src);
}

#endif	// end of Utility