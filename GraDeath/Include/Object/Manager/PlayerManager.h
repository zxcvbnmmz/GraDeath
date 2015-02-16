#ifndef _PLAYER_MANAGER_H__
#define _PLAYER_MANAGER_H__

// 後々渡すデータの仮名称
typedef void* PlayerData;

namespace PlayerManager{
	bool Init(PlayerData* data);
	void Release();
	void Update();
	void Draw();


    int AllPlayerMove(int _movex, int _movey);
    void OnPlayerPos(int _Player, int _posx , int _posy);

};

#endif	// end of PlayerManager