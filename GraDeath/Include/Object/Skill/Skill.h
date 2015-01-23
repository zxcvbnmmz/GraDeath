#ifndef _SKILL_H_
#define _SKILL_H_

#include "Object/Skill/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"
#include "Object/ObjectParameter.h"
#include <memory>
#include <vector>
#include <string>

class Sprite;
struct D3DXVECTOR2;
struct CellData;

class Skill
{
protected:
	std::shared_ptr< Sprite > skillAnim;
	AnimationData animSkill;
	int frameCount = 0;
	int animeMax = 0;
	int nowAnime = 0;
	int nowFrame = 0;
	bool skillFlg = false;
	D3DXVECTOR2 pos;
	std::vector<std::shared_ptr<CellData>>::iterator currentCell;

	unsigned int dirFlg;

public:
	Skill (){}

	~Skill (){}

	void Init ( std::string _filename, std::wstring _path, int skill_id );

	virtual void Update ();

	virtual void Draw ();

	virtual void SetPosition ( const D3DXVECTOR2& _pos, unsigned int _dirFlg );

	D3DXVECTOR2& GetPosition ();

	virtual void Move (){}

	void SkillOn ();

	void SkillOff ();

	void SetSize ( const D3DXVECTOR2& _pos );

	AnimationData& GetAnimationData ();


};

#endif