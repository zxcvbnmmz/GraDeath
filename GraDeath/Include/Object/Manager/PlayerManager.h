#ifndef _PLAYER_MANAGER_H__
#define _PLAYER_MANAGER_H__

// ��X�n���f�[�^�̉�����
typedef void* PlayerData;

namespace PlayerManager{
	bool Init(PlayerData* data);
	void Release();
	void Update();
	void Draw();
    void AllPlayerMove(int movex, int movey);
    void OnPlayerPos(int _Player, int _posx , int _posy);
};

#endif	// end of PlayerManager