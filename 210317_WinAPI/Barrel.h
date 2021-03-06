#pragma once
#include "GameNode.h"

class CollisionCheck;
class MissileManager;
class Barrel
{
private:
	CollisionCheck* collisionCheck;

	FPOINT barrelStart;
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;
	bool isActivated;

	int currFrameX;
	int updateCount;
	int missileType;
	FPOINT pos;
	string name;
	RECT shape;
	float moveSpeed;
	bool isAlive;
	float angle;

	int missileSize;

	int dir;
	FIRETYPE fireType;
	float maxFireCount;


	// �̻���
	MissileManager* myMissile; //���� �ʿ�
	float fireCount;
	
public:
	HRESULT Init(CollisionCheck* collisionCheck, int posX = 0, int posY = 0);
	virtual HRESULT Init() { return E_FAIL; };
	void Release();
	void Update();
	void Render(HDC hdc);
	void Attack();

	inline void SetAngle(float angle) { this->barrelAngle = angle; }
	inline void SetActivated(bool isActivated) { this->isActivated = isActivated; }
	inline void SetBarrelSize(int barrelSize) { this->barrelSize = barrelSize; }
	inline void SetFireType(FIRETYPE fireType) { this->fireType = fireType; }
	inline void SetMaxFireCount(float maxFireCount) { this->maxFireCount = maxFireCount; }
	inline bool GetActivated() { return isActivated; }

	void Move();
	void HorizonMove();	

	inline void SetSize(int size) { this->barrelSize = size; }
	inline void SetBarrelPos(FPOINT pos) { this->barrelStart = pos; }
	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetIsAlive() { return this->isAlive; }
	inline void SetMissileType(int type) { this->missileType = type; }
	inline void SetbarrelEnd( FPOINT barrelEnd) { this->barrelEnd = barrelEnd; }
	inline FIRETYPE GetFireType() { return fireType; }
	inline FPOINT GetstartPos() {return barrelStart;}//포신을 보스에서 돌려줄려고 가져옴
	inline float GetAngle() { return barrelAngle; }
	inline int GetSize() { return barrelSize; }
	inline void SetMissileSize(int missileSize) { this->missileSize = missileSize; }
	
	//inline void SetPos(FPOINT pos) { this->barrelStart = pos; }
};

