#ifndef _D3D_CORE_H__
#define _D3D_CORE_H__

#include <d3d10_1.h>

namespace D3DCore{
	HRESULT Init(HWND hwnd, int width, int height);
	void	Destroy();
	HRESULT Clear(float* color, unsigned int clearFlag);

	HRESULT ClearStencil();
	void Draw(unsigned numIndex, unsigned startIndexLocation);
	void Draw(unsigned numIndex, unsigned startIndexLocation, int baseVertexLocation);

	void SetDefaultRenderTarget();
	ID3D10Device1* GetD3DDevice();
};

#endif	// end of D3DCore