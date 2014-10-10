#ifndef _SYSTEM_H__
#define _SYSTEM_H__

#include <D3D10_1.h>

namespace System{
	bool Initialize(HINSTANCE hInstance);
	bool Loop();
	void Release();
};

#endif	// end of System