#include "System/D3DCore.h"
#include "Graphic/Rasterizer/Rasterizer.h"
#include "Graphic/D3DGraphic.h"
#include <atlbase.h>

namespace Graphic{
	namespace Rasterizer{
		class Pimpl;
	}
}

using namespace Graphic;

class Rasterizer::Pimpl{
public:
	Pimpl(){}	

	HRESULT CreateState(D3D10_CULL_MODE cull, D3D10_FILL_MODE fill, ID3D10RasterizerState** dst);

	CComPtr<ID3D10RasterizerState> cullNone;
	CComPtr<ID3D10RasterizerState> cullClockWise;
	CComPtr<ID3D10RasterizerState> cullCounterClockWise;
	CComPtr<ID3D10RasterizerState> wireFrame;
};

namespace {
	Rasterizer::Pimpl pimpl;
}

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

	return D3DCore::GetD3DDevice()->CreateRasterizerState(&desc, dst);
}

void Rasterizer::CullNone(){
	if(!pimpl.cullNone && FAILED(pimpl.CreateState(D3D10_CULL_NONE, D3D10_FILL_SOLID, &pimpl.cullNone))){
		return;
	}

	Graphic::D3D::RS::SetRasterizeState(pimpl.cullNone);
}

void Rasterizer::CullClockWise(){
	if(!pimpl.cullClockWise && FAILED(pimpl.CreateState(D3D10_CULL_FRONT, D3D10_FILL_SOLID, &pimpl.cullClockWise))){
		return;
	}
	Graphic::D3D::RS::SetRasterizeState(pimpl.cullClockWise);
}

void Rasterizer::CullCounterClockWise(){
	if(!pimpl.cullCounterClockWise && FAILED(pimpl.CreateState(D3D10_CULL_BACK, D3D10_FILL_SOLID, &pimpl.cullCounterClockWise))){
		return ;
	}
	Graphic::D3D::RS::SetRasterizeState(pimpl.cullCounterClockWise);
}

void Rasterizer::WireFrame(){
	if(!pimpl.wireFrame && FAILED(pimpl.CreateState(D3D10_CULL_BACK, D3D10_FILL_WIREFRAME, &pimpl.wireFrame))){
		return;
	}
	Graphic::D3D::RS::SetRasterizeState(pimpl.wireFrame);
}

