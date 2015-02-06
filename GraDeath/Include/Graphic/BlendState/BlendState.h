#ifndef _BLEND_STATE_H__
#define _BLEND_STATE_H__

struct ID3D10BlendState;

namespace Graphic{
namespace BlendState{
	void Add();
	void AlphaBlend();
	void Multiple();
	void Lenear();
	void Default();
};
}

#endif	// end of BlendState
