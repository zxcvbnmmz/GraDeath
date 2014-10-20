#ifndef _BLEND_STATE_H__
#define _BLEND_STATE_H__

struct ID3D10BlendState;

namespace Graphic{
namespace BlendState{
	ID3D10BlendState* Add();
	ID3D10BlendState* AlphaBlend();
	ID3D10BlendState* Multiple();
	ID3D10BlendState* Lenear();
	ID3D10BlendState* Default();
};
}

#endif	// end of BlendState