#ifndef _ANIMATION_MANAGER_H__
#define _ANIMATION_MANAGER_H__

struct AnimeData;

namespace AnimationManager{
	AnimeData* Get ( const char* tag );
	bool Load ( const char* fileName, const char* tag = "" );
	bool Release ( const char* tag );
	void Release ();
};

#endif	// end of AnimationManager