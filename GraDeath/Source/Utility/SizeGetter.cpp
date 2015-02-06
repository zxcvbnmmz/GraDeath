#include "Utility/SizeGetter.h"
#include <d3dx9tex.h>

#pragma comment (lib,"d3dx9.lib")

void GetTextureSize(LPCWSTR fileName, D3DXVECTOR2* size){
	D3DXIMAGE_INFO info;
	D3DXGetImageInfoFromFile(fileName, &info);
	size->x = (FLOAT)info.Width;
	size->y = (FLOAT)info.Height;
}
