#ifndef _BLEND_STATE_H__
#define _BLEND_STATE_H__

struct ID3D10BlendState;

namespace Graphic{
class BlendState{
public:
	BlendState();
	~BlendState();

	ID3D10BlendState* Add()const;
	ID3D10BlendState* AlphaBlend()const;
	ID3D10BlendState* Multiple()const;
	ID3D10BlendState* Lenear()const;
	ID3D10BlendState* Default()const;

private:
	class Pimpl;
	Pimpl* pimpl;
};
}

#endif	// end of BlendState