#ifndef _STAGE_H__
#define _STAGE_H__

class b2Body;

namespace Stage{
    bool Initialize(int stageID);
	void Draw();
	void Release();
    float GetStageHP();
    void StageDamage(float _damage);
    void SetStageHP(float _HP,int playernum);
    bool GetStageStatus();
    void CriateStage();
    int StageBrakePlayerNum();

	b2Body* GetBreakbleStage();
	b2Body* GetUnbreakbleStage();
    bool GetSkillEnd();
    void AttachFixture()
};

#endif	// end of Stage