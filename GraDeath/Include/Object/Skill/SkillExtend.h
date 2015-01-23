#ifndef _SKILL_EXTEND_H_
#define _SKILL_EXTEND_H_

#include "Object/Skill/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"
#include "Object/ObjectParameter.h"
#include "Object/Skill/Skill.h"
#include <memory>
#include <vector>
#include <string>

class Sprite;
struct D3DXVECTOR2;
struct CellData;

class SkillExtend
{
protected:
	std::vector< Sprite* > sprite;
	AnimationData animSkill;
	D3DXVECTOR2 pos;
	std::vector<std::shared_ptr<CellData>>::iterator currentCell;

	unsigned int dirFlg;

public:
	SkillExtend (){}

	~SkillExtend (){}

	void Init ( std::string _filename, std::wstring _path, int skill_id );

	virtual void Update ();

	virtual void Draw ();

	virtual void SetPosition ( const D3DXVECTOR2& _pos, unsigned int _dirFlg );

	D3DXVECTOR2& GetPosition ();

	virtual void Move (){}

	void SkillOn ();

	void SkillOff ();

	AnimationData& GetAnimationData ();


};

#endif