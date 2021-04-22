#pragma once
#include "GameNode.h"

class Image;
class Missile;
class Enemy;
class Item;
class CollisionCheck : public GameNode
{
private:
	int keyCnt;
	Image* hitImg;
	int frameCount;
	int currFrameX; 
	bool hitted;
	FPOINT hitPos;
	float time;

	//������ 1�� power, 2�� bomb, 3�� life
	int item;
	RECT RectHit_item;
	bool bombIsCollision;
	bool powerIsCollision;
	bool lifeIsCollision;
	list<Item*> itemData;

	//�÷��̾� ��ź ���� ����
	bool bombUse;
	RECT RectHit_Bomb;

	//�÷��̾� �浹���� ����
	RECT RectHit_Player;
	bool playerIsCollision;
	bool isPlayerAlive;

	//�÷��̾� �̻��� �浹���� ����
	list<Missile*> playerMissile;
	
	//��� �浹
	list<Enemy*> enemyData;
	bool enemyIsCollision;
	bool isEnemyAlive;

	//���� �浹���� ����
	RECT RectHit_Boss;
	bool bossIsCollision;
	bool isBossAlive;

	//���� �̻��� �浹���� ����
	list<Missile*> bossMissile;

	//���� ������ ������ RECT
	RECT rcTemp;

public:
	HRESULT Init();
	void Release();
	void Update();
	void RendEffect(HDC hdc, FPOINT pos);
	void Render(HDC hdc);

	//�÷��̾�
	inline void SetPlayerRect(RECT rect) { this->RectHit_Player = rect; }
	inline void SetPlayerMissile(Missile* missile) { this->playerMissile.push_back(missile); }
	inline void DeletePlayerMissile(Missile* missile) { this->playerMissile.remove(missile); }
	inline void GetPlayerAlive(bool alive) { this->isPlayerAlive = alive; }

	inline bool GetPlayerCollision() { return playerIsCollision; }
	inline void SetPlayerCollision(bool coll) { this->playerIsCollision = coll; }

	//����
	inline void SetBossRect(RECT rect) { this->RectHit_Boss = rect; }
	inline void SetBossMissile(Missile* missile) { this->bossMissile.push_back(missile); }
	inline void DeleteBossMissile(Missile* missile) { this->bossMissile.remove(missile); }
	inline void GetBossAlive(bool alive) { this->isBossAlive = alive; }

	inline bool GetBossCollision() { return bossIsCollision; }
	inline void SetBossCollision(bool coll) { this->bossIsCollision = coll; }

	//���
	inline void SetEnemy(Enemy* enemy) { this->enemyData.push_back(enemy); }
	
	inline bool GetEnemyCollision() { return enemyIsCollision; }
	inline void SetEnemyCollision(bool coll) { this->enemyIsCollision = coll; }
	inline void DeleteEnemy(Enemy* enemy) { this->enemyData.remove(enemy); }
	void DeleteEnemyMissile(Missile* missile);
	inline void GetEnemyAlive(bool alive) { this->isEnemyAlive = alive; }

	//��ź
	inline void SetBombUse(bool use) { this->bombUse = use; }
	inline void SetBombRect(RECT rect) { this->RectHit_Bomb = rect; }

	//������
	inline void SetItem(Item* item) { this->itemData.push_back(item); }
	inline void SetItem(int num) { this->item = num; }

	inline int GetPowerCollision() { return this->powerIsCollision; }
	inline void SetPowerCollision(bool coll) { this->powerIsCollision = coll; }

	inline int GetBombCollision() { return this->bombIsCollision; }
	inline void SetBombCollision(bool coll) { this->bossIsCollision = coll; }

	inline int GetLifeCollision() { return this->lifeIsCollision; }
	inline void SetLifeCollision(bool coll) { this->lifeIsCollision = coll; }
};

