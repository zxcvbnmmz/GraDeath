#ifndef _DEPTH_STENCIL_H__
#define _DEPTH_STENCIL_H__

struct ID3D10DepthStencilState;

namespace Graphic{
namespace DepthStencil{
	void DepthNone();
	void DepthDefault();
	void DepthRead();
};
}

#endif	// end of DepthStencil