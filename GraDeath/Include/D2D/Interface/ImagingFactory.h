#ifndef _IMAGING_FACTORY_H__
#define _IMAGING_FACTORY_H__

#include <atlbase.h>

struct IWICImagingFactory;

namespace D2D{
	namespace ImagingFactory{
		bool Create();
		void Release();
		CComPtr<IWICImagingFactory> Get();
	}
}
#endif	// end of ImagingFactory