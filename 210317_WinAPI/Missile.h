#pragma once
#include "GameNode.h"

class Image;
class Enemy;
class Barrel;
class PlayerShip;
class SkillManager;
class SkillInterface;

class Missile : public GameNode
{
public:
	enum SKILLTYPE { NormalSkillTYPE, ZigzagSkillTYPE, MeteorSkillTYPE, WormSKillTYPE, TwoSKillTYPE, NotSkillTYPE };

protected:
	// ÀÌ¹ÌÁö
	Image* img;

	FPOINT pos;
	FPOINT startPos;
	float moveSpeed;
	float moveTime;
	int size;
	RECT shape;
	int damage;
	float angle;
	bool isFired;
	SKILLTYPE missileType;
	int fireIndex;
	int fireStep;

	Enemy* target;
	float destAngle;

	SkillManager* skillManager;

public:
	HRESULT Init(FPOINT position);
	virtual HRESULT Init() { return E_FAIL; };
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);
	
	inline void SetStartPos(FPOINT pos) { this->startPos = pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	void SetIsFired(bool isFired);
	inline bool GetIsFired() { return this->isFired; }

	inline void SetTarget(Enemy* target) { this->target = target; }
	inline SKILLTYPE GetType() { return this->missileType; }
	inline void SetType(SKILLTYPE type) { this->missileType = type; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
	//inline POINT GetTarget(POINT target) { return target; }

	inline int GetSize() { return this->size; }
};

