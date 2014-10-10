#include "Graphic/Graphic.h"
#include "System/D3DCore.h"
#include "D3D/SwapChain/SwapChain.h"

namespace Graphic{
	namespace{
		float clearColor[4] = {0,0,0,0};
	}

	void Present(UINT syncInterval, UINT flag){
		D3D::SwapChain::Present(syncInterval,flag);
	}

	void Clear(CLEAR_FLAG flag){
		D3DCore::Clear(clearColor, flag);
	}

	void SetClearColor(float r, float g, float b, float a){
		float color[4] = {r,g,b,a};
		memcpy(clearColor,color,sizeof(float)*4);
	}
};