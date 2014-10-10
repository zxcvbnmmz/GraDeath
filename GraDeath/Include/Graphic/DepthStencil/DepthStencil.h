#ifndef _DEPTH_STENCIL_H__
#define _DEPTH_STENCIL_H__

struct ID3D10DepthStencilState;

namespace Graphic{
class DepthStencil{
public:
	DepthStencil();

	ID3D10DepthStencilState* DepthNone()const;
	ID3D10DepthStencilState* DepthDefault()const;
	ID3D10DepthStencilState* DepthRead()const;

private:
	class Pimpl;
	Pimpl* pimpl;
};
}

#endif	// end of DepthStencil