#include "Missile.h"
#include "Enemy.h"
#include "CommonFunction.h"
#include "Image.h"
#include <math.h>
#include "SkillManager.h"
#include "NormalSkill.h"
#include "FallingKnivesSkill.h"
#include "FireworkSkill.h"

HRESULT Missile::Init(FPOINT position)
{
	startPos = position;
	pos = {-100, -100};
	// (�ӷ� = �Ÿ� / �ð�)
	// moveSpeed * (elapsedTime / moveTime) = moveSpeed / (moveTime / elapsedTime)
	moveTime = 2.0f;	//10�� ����
	moveSpeed = 500;	//500�� �̵��ϰ� �ʹ�

	size = 25;
	shape = { 0, 0, 0, 0 };
	damage = 5000;
	angle = 0.0f;
	isFired = false;
	missileType = SKILLTYPE::FIREWORKTYPE;
	fireStep = 0;
	target = nullptr;
	destAngle = 0.0f;


	// �̹���
	img = ImageManager::GetSingleton()->FindImage("EnemyMissile");
	if (img == nullptr)
	{
		MessageBox(g_hWnd, "enemy missile �� �ش��ϴ� �̹����� �߰����� �ʾ���", "���", MB_OK);
		return E_FAIL;
	}

	skillManager = new SkillManager();
	skillManager->ChangeSkill(new FireworkSkill());

    return S_OK;
}

void Missile::Release()
{
}

void Missile::Update()
{
	//���� ��Ų �̻��� Ÿ����, �߻� ��ų ��������
	if (isFired)
	{
		switch (missileType)
		{
		case SKILLTYPE::NormalSkillTYPE:
			//skillManager->ChangeSkill(new NormalSkill());
			break;

		case SKILLTYPE::FallingKnivesTYPE:
			break;

		case SKILLTYPE::FIREWORKTYPE:
			break;
		default:
			break;
		}
		skillManager->UseSkill(this, lpTargetPos);

		if (pos.x < 0 || pos.y < 0 || pos.x > WINSIZE_X || pos.y > WINSIZE_Y)
		{
			moveSpeed = 500.0f;
			skillManager->Renew();
			isFired = false;
			fireStep = 0;
		}
	}

	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
}

void Missile::Render(HDC hdc)
{
	if (isFired)
	{
		img->Render(hdc, pos.x, pos.y, true);
		//img->Render(hdc, pos.x - (size / 2), pos.y - (size / 2));
		//Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
	pos.x = startPos.x;
	pos.y = startPos.y;
}

