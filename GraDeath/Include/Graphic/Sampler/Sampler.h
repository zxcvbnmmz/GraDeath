#ifndef _SAMPLER_H__
#define _SAMPLER_H__

namespace Sampler{
	void SetPointWrap(unsigned int slot = 0);
	void SetPointClamp(unsigned int slot = 0);
	void SetLinearWrap(unsigned int slot = 0);
	void SetLinearClamp(unsigned int slot = 0);
	void SetAnisotropicWrap(unsigned int slot = 0);
	void SetAnisotropicClamp(unsigned int slot = 0);
};

#endif	// end of Sampler