#ifndef _BGM_MANAGER_H__
#define _BGM_MANAGER_H__

#include <map>
#include "Sound/BGM/BGM.h"

class BGMManager{
private:
	BGMManager(){}
	BGMManager(const BGMManager&);
	BGMManager& operator=(const BGMManager&);

public:
	~BGMManager();

	static BGMManager* GetInstance(){
		if (inst == nullptr){
			inst = new BGMManager;
		}
		return inst;
	}

	static void Release();

	void Load(char* fileName);

	void Play(char* fileName);
	void Stop(char* fileName);




private:
	static BGMManager* inst;
	std::map<char*, BGM> BGMs;
};

BGMManager* BGMManager::inst = nullptr; 


#endif	// end of BGMManager