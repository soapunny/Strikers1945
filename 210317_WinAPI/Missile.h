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
	enum SKILLTYPE { 
		NormalSkill_TYPE, ZigzagSkill_TYPE, FallingKnives_TYPE, FIREWORK_TYPE
		, CircularSkill_TYPE, Guided_Skill_TYPE, PlayerSkill_TYPE
		, MeteorSkill_TYPE, WormSKill_TYPE, TwoSKill_TYPE, NotSkill_TYPE
		, TornadoSkill_TYPE, END_TYPE};

protected:
	// ¿ÃπÃ¡ˆ
	Image* img;

	FPOINT playerPos;
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
	SkillInterface* lpCurrSkill;
	int fireIndex;
	int fireStep;

	Enemy* target;
	FPOINT* lpTargetPos;
	float destAngle;

	SkillManager* skillManager;
	vector<SkillInterface*> vSkillInterfaces;

public:
	HRESULT Init(FPOINT position);
	virtual HRESULT Init() { return E_FAIL; };
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);
	
	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
	inline FPOINT GetPlayerPos() { return this->playerPos; }

	inline void SetStartPos(FPOINT pos) { this->startPos = pos; }
	inline FPOINT GetStartPos() { return this->startPos; }
	
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline void SetLpTargetPos(FPOINT* pos) { this->lpTargetPos = pos; }
	inline void SetMoveSpeed(float moveSpeed) { this->moveSpeed = moveSpeed; }
	inline float GetAngle() { return this->angle; }
	inline FPOINT GetPos() { return this->pos; }
	
	void SetIsFired(bool isFired);
	inline bool GetIsFired() { return this->isFired; }
	inline float GetMoveSpeed() { return this->moveSpeed; }
	inline float GetMoveTime() { return moveTime; }
	inline void SetTarget(Enemy* target) { this->target = target; }

	inline SKILLTYPE GetType() { return this->missileType; }
	inline void SetType(SKILLTYPE type) { this->missileType = type; }
	
	inline void SetAngle(float angle) { this->angle = angle; }
	//inline void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
	inline void SetFireIndex(int fireIndex) { this->fireIndex = fireIndex; }
	//inline POINT GetTarget(POINT target) { return target; }

	inline int GetSize() { return this->size; }
};