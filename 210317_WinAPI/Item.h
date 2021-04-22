#pragma once
#include "GameNode.h"

class CollisionCheck;
class Image;
class ItemManager;
class Item : public GameNode
{	
protected:
	FPOINT dropPos;
	
	RECT itemRect;

	ItemManager* itemManager;
	CollisionCheck* collisionCheck;
	bool isFired;
	Image* img;
	FPOINT ItemPos;
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
	inline bool GetIsFired() { return this->isFired; }
	inline void SetDropPos(FPOINT dropPos) { this->dropPos = dropPos; }
	inline bool GetWhy() { return this->why; }

	inline RECT* GetItemRect() { return &(this->itemRect); }
	inline void SetItemRectZero() { this->itemRect = { -100, -100, -100, -100 }; }
};

