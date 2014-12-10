#ifndef _MEMORY_H__
#define _MEMORY_H__

#include <D3D10_1.h>
#include <D3DX10math.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#define new ::new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

template <class T>
inline void SafeDelete(T* t){
	if (t){
		delete t;
		t = nullptr;
	}
}

template <class T>
inline void SafeArrayDelete(T* t){
	if (t){
		delete[] t;
		t = nullptr;
	}
}

template <class T>
inline void SafeRelease(T* t){
	if (t){
		t->Release();
		t = nullptr;
	}
}

#endif	// end of Memory
