#ifndef _SKILL_H_
#define _SKILL_H_

#include "Object/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"
#include "Object/ObjectParameter.h"
#include <memory>
#include <vector>

class Sprite;
struct D3DXVECTOR2;
struct CellData;

class Skill
{
private:
	std::shared_ptr< Sprite > skillAnim;
	AnimationData animSkill;
	int frameCount = 0;
	int animeMax = 0;
	int nowAnime = 0;
	bool skillFlg = false;
	D3DXVECTOR2 pos;
	std::vector<std::shared_ptr<CellData>>::iterator currentCell;

public:
	Skill (){}

	~Skill (){}

	void Init ( char* _filename );

	void Update ();

	void Draw ();

	void SetPosition ( const D3DXVECTOR2& _pos );

	void SkillOn ();

	AnimationData& GetAnimationData ();

};

#endif