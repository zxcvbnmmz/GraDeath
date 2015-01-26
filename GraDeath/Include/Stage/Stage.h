#ifndef _STAGE_H__
#define _STAGE_H__

namespace Stage{
	void SetStageID (int stageID);
    bool Initialize(int stageID);
	void Draw();
	void Release();
    float GetStageHP();
    void StageDamage(float _damage);
    void SetStageHP(float _HP,int playernum);
    bool GetStageStatus();
    void CriateStage();
    int StageBrakePlayerNum();
};

#endif	// end of Stage