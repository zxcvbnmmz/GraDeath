#ifndef _WRITE_FACTORY_H__
#define _WRITE_FACTORY_H__

#include <atlbase.h>

struct IDWriteFactory;

namespace D2D{
	namespace WriteFactory{
		bool Create();
		void Release();
		CComPtr<IDWriteFactory> Get();
	}
}

#endif	// end of WriteFactory