#pragma once
#include "config.h"
// ��� ����, ��� �Լ� ���� ���� ����

/*
	������ ������� ���ӱ����� ���� �⺻�� �Ǵ� Ŭ����
*/
class GameNode
{
public:
	virtual HRESULT Init() = 0;			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release() = 0;			// �޸� ����
	virtual void Update() = 0;			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc) = 0;	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	GameNode() {};
	virtual ~GameNode() {};
};

