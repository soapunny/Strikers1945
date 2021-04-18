#pragma once
#include "GameNode.h"

class MissileManager;
class Barrel
{
private:
	// ����(������ ������, ����)	���� �ʿ�
	FPOINT barrelStart;
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;
	bool isActivated;

	// �̻���
	MissileManager* myMissile; //���� �ʿ�
	int fireCount;
public:
	HRESULT Init(FPOINT pos);
	void Release();
	void Update();
	void Render(HDC hdc);
	void Attack();

	inline void SetPos(FPOINT pos) { this->barrelStart = pos; }
	inline void SetAngle(float angle) { this->barrelAngle = angle; }
	inline void SetActivated(bool isActivated) { this->isActivated = isActivated; }
};

