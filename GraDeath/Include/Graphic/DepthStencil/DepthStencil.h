#ifndef _DEPTH_STENCIL_H__
#define _DEPTH_STENCIL_H__

struct ID3D10DepthStencilState;

namespace Graphic{
namespace DepthStencil{
	ID3D10DepthStencilState* DepthNone();
	ID3D10DepthStencilState* DepthDefault();
	ID3D10DepthStencilState* DepthRead();
};
}

#endif	// end of DepthStencil