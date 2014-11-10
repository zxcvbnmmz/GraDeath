#ifndef _PLAYER_MANAGER_H__
#define _PLAYER_MANAGER_H__

// 後々渡すデータの仮名称
typedef void* PlayerData;

namespace PlayerManager{
	bool Init(PlayerData* data);
	void Update();
	void Draw();
};

#endif	// end of PlayerManager