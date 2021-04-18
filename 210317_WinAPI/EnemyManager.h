#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;

class EnemyManager: public GameNode
{
private:
	vector<Enemy*> vEnemys;	
	//<Enemy>�� Enemy classũ�⸸ŭ ���������� 
	//<Enemy*>�� ������ ũ���� 4byte�� �����´�
	//< >�� ���ø�
	FPOINT playerPos;

public:
	HRESULT Init();		// �������̵� : ������
	void Release();
	void Update();
	void Render(HDC hdc);

	void AddEnemy(int size);
	inline void SetPlayerPos(FPOINT pos) { this->playerPos = pos; }
};

