#include "System/D3DCore.h"
#include "Graphic/Rasterizer/Rasterizer.h"
#include <atlbase.h>

using namespace Graphic;

class Rasterizer::Pimpl{
public:
	Pimpl(ID3D10Device* _device):device(_device){}
	static Pimpl* GetInstance(){
		static Pimpl pimpl(D3DCore::GetD3DDevice());
		return &pimpl;
	}

	HRESULT CreateState(D3D10_CULL_MODE cull, D3D10_FILL_MODE fill, ID3D10RasterizerState** dst);

	CComPtr<ID3D10RasterizerState> cullNone;
	CComPtr<ID3D10RasterizerState> cullClockWise;
	CComPtr<ID3D10RasterizerState> cullCounterClockWise;
	CComPtr<ID3D10RasterizerState> wireFrame;

private:
	ID3D10Device* device;
};

HRESULT Rasterizer::Pimpl::CreateState(D3D10_CULL_MODE cull, D3D10_FILL_MODE fill, ID3D10RasterizerState** dst){
	if(*dst != nullptr){
		return S_OK;
	}

	D3D10_RASTERIZER_DESC desc;
	ZeroMemory( &desc, sizeof(desc));
	desc.CullMode =cull;
	desc.FillMode = fill;
	desc.DepthClipEnable = true;
	desc.MultisampleEnable = true;

	return device->CreateRasterizerState(&desc,dst);
}

Rasterizer::Rasterizer():pimpl(Pimpl::GetInstance()){}

ID3D10RasterizerState* Rasterizer::CullNone()const{
	if(!pimpl->cullNone && FAILED(pimpl->CreateState(D3D10_CULL_NONE, D3D10_FILL_SOLID, &pimpl->cullNone))){
		return nullptr;
	}
	return pimpl->cullNone;
}

ID3D10RasterizerState* Rasterizer::CullClockWise()const{
	if(!pimpl->cullClockWise && FAILED(pimpl->CreateState(D3D10_CULL_FRONT, D3D10_FILL_SOLID, &pimpl->cullClockWise))){
		return nullptr;
	}
	return pimpl->cullClockWise;
}

ID3D10RasterizerState* Rasterizer::CullCounterClockWise()const{
	if(!pimpl->cullCounterClockWise && FAILED(pimpl->CreateState(D3D10_CULL_BACK, D3D10_FILL_SOLID, &pimpl->cullCounterClockWise))){
		return nullptr;
	}
	return pimpl->cullCounterClockWise;
}

ID3D10RasterizerState* Rasterizer::WireFrame()const{
	if(!pimpl->wireFrame && FAILED(pimpl->CreateState(D3D10_CULL_BACK, D3D10_FILL_WIREFRAME, &pimpl->wireFrame))){
		return nullptr;
	}
	return pimpl->wireFrame;
}

