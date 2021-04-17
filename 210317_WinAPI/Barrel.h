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

	// �̻���
	MissileManager* myMissile; //���� �ʿ�
	int fireCount;
public:
	HRESULT Init(FPOINT pos);
	void Release();
	void Update();
	void Render(HDC hdc);

	inline void SetPos(FPOINT pos) { this->barrelStart = pos; }
	inline void SetbarrelEnd( FPOINT barrelEnd) { this->barrelEnd = barrelEnd; }

	inline FPOINT GetstartPos() {return barrelStart;}//������ �������� �����ٷ��� ������
	inline float GetAngle() { return barrelAngle; }
	inline int GetSize() { return barrelSize; }
	//inline void SetPos(FPOINT pos) { this->barrelStart = pos; }
};

