#include "Utility/Converter.h"
#include <locale.h>

namespace Utility{
	namespace {
		static const char* locale = (LC_ALL, "japanese");
	};

	const char* ConvertToChar(char* dst, LPCWSTR str){
		size_t wLen = 0;
		errno_t err = 0;

		size_t size = wcslen(str);

		err = wcstombs_s(&wLen, dst, size + 1, str, _TRUNCATE);
		return dst;
	}

	LPCWSTR ConvertToWChar(LPWSTR dst, const char* str){
		size_t wLen = 0;
		errno_t err = 0;

		size_t size = strlen(str);

		err = mbstowcs_s(&wLen, dst, size + 1, str, _TRUNCATE);
		return dst;
	}

	const char* ConvertToSJis(char* dst, LPWSTR byteArray){
		size_t size = WideCharToMultiByte(CP_ACP, 0, byteArray, -1, NULL, 0, NULL, NULL);

		// UTF-16•¶Žš—ñ‚©‚çShift-JIS‚É•ÏŠ·‚·‚éB
		WideCharToMultiByte(CP_ACP, 0, byteArray, -1, dst, size + 1, NULL, NULL);
		return dst;
	}

	LPWSTR ConvertToUTF_16(LPWSTR dst, const char* src){
		size_t strSize = strlen(src);
		// Shift-JIS•¶Žš—ñ‚©‚çUTF-16‚É•ÏŠ·‚µ‚½‚Æ‚«‚Ì•¶Žš—ñ’·‚ð‹‚ß‚éB
		size_t size = MultiByteToWideChar(CP_ACP, 0, src, strSize, NULL, 0);

		// Shift-JIS•¶Žš—ñ‚©‚çUTF-16‚É•ÏŠ·‚·‚éB
		MultiByteToWideChar(CP_ACP, 0, src, strSize, dst, size + 1);
		return dst;
	}

	D3DXMATRIX* ConvertToMatrix(D3DXMATRIX* dst, D3DXQUATERNION* src){
		//dst->_11 = 1.0f - 2.0f * src->y * src->y - 2.0f * src->z * src->z;
		//dst->_12 = 2.0f * src->x * src->y + 2.0f * src->w * src->z;
		//dst->_13 = 2.0f * src->x * src->z - 2.0f * src->w * src->y;

		//dst->_21 = 2.0f * src->x * src->y - 2.0f * src->w * src->z;
		//dst->_22 = 1.0f - 2.0f * src->x * src->x - 2.0f * src->z * src->z;
		//dst->_23 = 2.0f * src->y * src->z + 2.0f * src->w * src->x;

		//dst->_31 = 2.0f * src->x * src->z + 2.0f * src->w * src->y;
		//dst->_32 = 2.0f * src->y * src->z - 2.0f * src->w * src->x;
		//dst->_33 = 1.0f - 2.0f * src->x * src->x - 2.0f * src->y * src->y;

		D3DXMatrixRotationQuaternion(dst, src);

		return dst;
	}

	D3DXQUATERNION* ConvertToQuaternion(D3DXQUATERNION* dst, D3DXMATRIX* src){
		float elem[4];
		elem[0] = src->_11 - src->_22 - src->_33 + 1.0f;
		elem[1] = -src->_11 + src->_22 - src->_33 + 1.0f;
		elem[2] = -src->_11 - src->_22 + src->_33 + 1.0f;
		elem[3] = src->_11 + src->_22 + src->_33 + 1.0f;

		unsigned int biggest = 0;
		for (int i = 1; i<4; ++i){
			if (elem[i]>elem[biggest]){
				biggest = i;
			}
		}

		if (elem[biggest] < 0.0f){
			return nullptr;
		}

		float v = sqrtf(elem[biggest])*0.5f;
		(*dst)[biggest] = v;
		float mul = 0.25f / v;

		switch (biggest){
		case 0:
			(*dst)[1] = (src->_12 + src->_21) * mul;
			(*dst)[2] = (src->_31 + src->_13) * mul;
			(*dst)[3] = (src->_23 - src->_32) * mul;
			break;
		case 1:
			(*dst)[0] = (src->_12 + src->_21) * mul;
			(*dst)[2] = (src->_23 + src->_32) * mul;
			(*dst)[3] = (src->_31 - src->_13) * mul;
			break;
		case 2:
			(*dst)[0] = (src->_31 + src->_13) * mul;
			(*dst)[1] = (src->_23 + src->_32) * mul;
			(*dst)[3] = (src->_12 - src->_21) * mul;
			break;
		case 3:
			(*dst)[0] = (src->_23 - src->_32) * mul;
			(*dst)[1] = (src->_31 - src->_13) * mul;
			(*dst)[2] = (src->_12 - src->_21) * mul;
			break;
		}

		return dst;
	}

	namespace Reject{

		bool ConvertToShaderResourceView(ID3D10ShaderResourceView** dst, LPCWSTR fileName, ID3D10Device* device){
			HANDLE file;
			HANDLE map = nullptr;
			void* pointer = nullptr;
			DWORD fileSize = 0;

			file = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

			if (file == INVALID_HANDLE_VALUE){
				return false;
			}

			DWORD mapFlag = PAGE_READWRITE;
			map = CreateFileMapping(file, 0, mapFlag, 0, 0, fileName);

			if (map <= 0){
				CloseHandle(file);
				return false;
			}

			DWORD mapviewFlag = FILE_MAP_WRITE;
			pointer = (char*)MapViewOfFile(map, mapviewFlag, 0, 0, 0);
			if (pointer == nullptr){
				CloseHandle(file);
				CloseHandle(map);
				return false;
			}

			DWORD high;
			fileSize = GetFileSize(file, &high);

			ID3D10ShaderResourceView* view = nullptr;
			HRESULT hr = D3DX10CreateShaderResourceViewFromMemory(device, pointer, fileSize, NULL, NULL, &view, NULL);

			return true;
		}
	}
}