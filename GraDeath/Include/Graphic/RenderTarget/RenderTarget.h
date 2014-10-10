#ifndef _RENDER_TEXTURE_H__
#define _RENDER_TEXTURE_H__

#include <atlbase.h>

struct ID3D10Texture2D;
struct ID3D10ShaderResourceView;
struct ID3D10DepthStencilView;
struct ID3D10RenderTargetView;
struct ID3D10Device1;

namespace Graphic{
class RenderTarget{
public:
	RenderTarget();

	enum CLEAR_FLAG{
		CLEAR_DEPTH = 0x1L,
		CLEAR_STENCIL = 0x2L,
		CLEAR_DEPTH_STENCIL = CLEAR_DEPTH|CLEAR_STENCIL
	};

	bool Initialize(unsigned int width, unsigned int height);
	void SetClearColor(float r, float g, float b, float a);
	void GetResource(CComPtr<ID3D10ShaderResourceView>& dst);
	void SetToShader(unsigned int slot = 0);
	void Begin();
	void End();
	void Clear(CLEAR_FLAG flag = CLEAR_DEPTH_STENCIL);

private:
	CComPtr<ID3D10Texture2D> renderTarget;
	CComPtr<ID3D10RenderTargetView> renderTargetView;
	CComPtr<ID3D10RenderTargetView> currentRenderTarget;

	CComPtr<ID3D10Texture2D> depthStencil;
	CComPtr<ID3D10DepthStencilView> depthStencilView;
	CComPtr<ID3D10DepthStencilView> currentStencilView;

	CComPtr<ID3D10ShaderResourceView> texture;
	ID3D10Device1* device;

	float clearColor[4];
};
}


#endif	// end of RenderTarget