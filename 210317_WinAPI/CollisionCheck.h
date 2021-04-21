#pragma once
#include "GameNode.h"

class Image;
class Missile;
class CollisionCheck : public GameNode
{
private:
	//�÷��̾� �浹���� ����
	RECT RectHit_Player;
	bool playerIsCollision;

	//�÷��̾� �̻��� �浹���� ����
	list<Missile*> playerMissile;

	//���� �浹���� ����
	RECT RectHit_Boss;
	bool bossIsCollision;

	//���� �̻��� �浹���� ����
	list<Missile*> bossMissile;

	//���� ������ ������ RECT
	RECT rcTemp;			

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	//�÷��̾�
	inline void SetPlayerRect(RECT rect) { this->RectHit_Player = rect; }
	inline void SetPlayerMissile(Missile* missile) { this->playerMissile.push_back(missile); }
	inline void DeletePlayerMissile(Missile* missile) { this->playerMissile.remove(missile); }

	inline bool GetPlayerCollision() { return playerIsCollision; }
	inline void SetPlayerCollision(bool coll) { this->playerIsCollision = coll; }

	//����
	inline void SetBossRect(RECT rect) { this->RectHit_Boss = rect; }
	inline void SetBossMissile(Missile* missile) { this->bossMissile.push_back(missile); }
	inline void DeleteBossMissile(Missile* missile) { this->bossMissile.remove(missile); }

	inline bool GetBossCollision() { return bossIsCollision; }
	inline void SetBossCollision(bool coll) { this->bossIsCollision = coll; }
};

