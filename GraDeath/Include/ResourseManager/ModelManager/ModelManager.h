#ifndef _MODEL_MANAGER_H__
#define _MODEL_MANAGER_H__

class CwnSkinMesh;
class CwnStaticMesh;

namespace ModelManager{

	namespace CWN{
		namespace SKIN{
			CwnSkinMesh* Get ( char* tag );
			bool Load ( char* fileName, char* path, const char* tag = "" );
			bool Release ( const char* tag );
			void Release ();
		};
		namespace STATIC{
			CwnStaticMesh* Get ( char* tag );
			bool Load ( char* fileName, char* path, const char* tag = "" );
			bool Release ( const char* tag );
			void Release ();
		};
	};
};

#endif	// end of ModelManager