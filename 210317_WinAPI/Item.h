#pragma once
#include "GameNode.h"

class MoveInterface;
class MoveManager;
class CollisionCheck;
class Image;
class ItemManager;
class Item : public GameNode
{	
protected:
	MoveManager* moveManager;
	FPOINT dropPos;
	
	ItemManager* itemManager;
	CollisionCheck* collisionCheck;
	bool isFired;
	Image* img;
	FPOINT ItemPos;
	vector<MoveInterface*> vMoveInterfaces;
	MoveInterface* currMoveInterface;
	float moveSpeed;
	float angle;
	int size;	
	bool why;
	int updateCount;
	int currFrameX;
public:
	virtual HRESULT Init() = 0;
	virtual HRESULT Init(CollisionCheck* collisionCheck) = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release() = 0;
	inline void SetIsFired(bool isFired) { this->isFired = isFired; }
	inline void SetDropPos(FPOINT dropPos) { this->dropPos = dropPos; }
	inline bool GetWhy() { return this->why; }
};

