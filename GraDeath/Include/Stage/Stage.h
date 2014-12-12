#ifndef _STAGE_H__
#define _STAGE_H__

namespace Stage{
    bool Initialize(int stageID);
	void Draw();
	void Release();
    float GetStageHP();
    void StageDamage(float _damage);
    void SetStageHP(float _HP);
};

#endif	// end of Stage