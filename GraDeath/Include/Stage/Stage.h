#ifndef _STAGE_H__
#define _STAGE_H__

#include <vector>
#include <memory>

using namespace std;


class b2Body;
class Sprite;

namespace Stage{
    bool Initialize(int stageID);
	void Draw();
	void Release();
    float GetStageHP();
    //void StageDamage(float _damage);
	void StageDamage ( float _damage, int _playernum );
    void SetStageHP(float _HP,int playernum);
    bool GetStageStatus();
    void CriateStage();
    int StageBrakePlayerNum();

	b2Body* GetBreakbleStage();
	b2Body* GetUnbreakbleStage();
    bool GetSkillEnd();
    void DettachFixture();
    void SetSkillEnd(bool isbool);
    void FadeDraw();
    void SetStagenum(int _ID);
    int GetStageNum();
    void CreateRedStage(Sprite* _sprite);
    void CreateBlueStage(Sprite* _sprite);
    void CreateSiroKuroStage(Sprite* _sprite);
    void CreateYellowStage(Sprite* _sprite);
    void CreateNoCollarStage(Sprite* _sprite);
    void SetCharaType(int _type);
    void PlaySpecialSkillSE(int _playertype);
    bool isPlaySE(int _playertype);
    D3DXVECTOR2 GetSpecialSkillpos(int _playertype);
    void SetSpecialSkill(int _playertype, int pos);
    void StageDraw(int _playernum);
};
#endif	// end of Stage