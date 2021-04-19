#include "PlayerShip.h"
#include "Image.h"
#include "MissileManager.h"
#include "CommonFunction.h"

HRESULT PlayerShip::Init()
{
	image = ImageManager::GetSingleton()->FindImage("�÷��̾� ���ּ�");
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "�÷��̾� ���ּ� �̹��� �ε� ����", "����", MB_OK);
		return E_FAIL;
	}
	currFrameX = 1;

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y + 50;

	moveSpeed = 300.0f;

	isAlive = true;
	isDying = false;
	canMove = false;

	playerLife = 100;

	collisionSize.x = 35;
	collisionSize.y = 50;

	playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };

	// �׽�Ʈ �� ���� //
	barrelSize = 2;
	barrelEnd[0] = { (pos.x - 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[1] = { (pos.x + 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[2] = { (pos.x + cosf(DegToRad(barrelAngle[2])) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelEnd[3] = { (pos.x + cosf(DegToRad(barrelAngle[3])) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelAngle[0] = 90;
	barrelAngle[1] = 90;
	barrelAngle[2] = 135;
	barrelAngle[3] = 45;

	// �׽�Ʈ �� ���� �̻���//
	for (int i = 0; i < 4; i++)
	{
		myMissile[i] = new MissileManager();
		myMissile[i]->Init(barrelEnd[i]);
		//myMissile[i]->SetAngle(barrelAngle[i]);
	}
	fireCount = 0;

	return S_OK;
}

void PlayerShip::Release()
{
	for (int i = 0; i < 4; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Release();
			delete myMissile[i];
			myMissile[i] = nullptr;
		}
	}
}

void PlayerShip::Update()
{
	playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	
	//ù ���� (�Ʒ����� ����)
	if (!canMove)
	{
		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= 1.0f;
		else
			canMove = true;
	}

	//���ĺ���
	if (isAlive && KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		isAlive = false;
		isDying = true;
	}

	//�̵�
	if (isDying)
	{
		OnDead();
	}
	else if(!isDying && canMove)
	{
		Move();
	}

	//
	RotateBarrel(3.14f / 4.0f);
	
	// ���� ��ġ, ������ ���� ��ǥ ���
	for (int i = 0; i < 2; i++)
	{
		barrelEnd[i] = { (pos.x - 10.0f + (20.0f * i)), (pos.y - barrelSize) };
	}

	for (int i = 2; i < 4; i++)
	{
		barrelEnd[i] = { ((pos.x - 10.0f + (20.0f * (i - 2))) + cosf(DegToRad(barrelAngle[i])) * barrelSize) , pos.y - barrelSize };
	}

	for (int i = 0; i < 4; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->SetPlayerPos(this->pos);
			myMissile[i]->SetPos(barrelEnd[i]);
			myMissile[i]->SetAngle(barrelAngle[i]);
			myMissile[i]->Update();
			//����
			Attack(i);
		}
	}
}

void PlayerShip::Render(HDC hdc)
{
	//�浹 �ڽ�
	 //playerRect = RenderRectToCenter(hdc, pos.x, pos.y, collisionSize.x, collisionSize.y);

	//life ǥ��
	wsprintf(szText, "LIFE: %d",playerLife);
	TextOut(hdc, WINSIZE_X - 150, 80, szText, strlen(szText));

	//�̹���
	if (image)
	{
		if(!isAlive)
			image->AlphaRender(hdc, pos.x, pos.y, true);
		if(isAlive)
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
	}

	// ����
	MoveToEx(hdc, pos.x-10, pos.y, NULL);
	LineTo(hdc, barrelEnd[0].x, barrelEnd[0].y);

	MoveToEx(hdc, pos.x+10, pos.y, NULL);
	LineTo(hdc, barrelEnd[1].x, barrelEnd[1].y);

	MoveToEx(hdc, pos.x - 10, pos.y, NULL);
	LineTo(hdc, barrelEnd[2].x, barrelEnd[2].y);

	MoveToEx(hdc, pos.x + 10, pos.y, NULL);
	LineTo(hdc, barrelEnd[3].x, barrelEnd[3].y);

	//�̻���5
	for (int i = 0; i < 4; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Render(hdc);
		}
	}
}

void PlayerShip::RotateBarrel(float angle)
{
}

void PlayerShip::Move()
{
	currFrameX = 1;
	collisionSize.x = 35;

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		collisionSize.x = 22;
		currFrameX = 0;
		if(pos.x > 20)
			pos.x -= moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		collisionSize.x = 22;
		currFrameX = 2;
		if (pos.x < WINSIZE_X - 20)
			pos.x += moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		if (pos.y > 30)
			pos.y -= moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		if (pos.y < WINSIZE_Y - 30)
			pos.y += moveSpeed * TimerManager::GetSingleton()->getElapsedTime();
	}
}

void PlayerShip::OnDead()
{
	if (image)
	{
		BLENDFUNCTION* blendFunc = image->GetBlendFunc();
		if (blendFunc->SourceConstantAlpha > 0)
		{
			blendFunc->SourceConstantAlpha--;
		}
		else
		{
			isDying = false;
			isAlive = false;
		}
	}
}

void PlayerShip::Attack(int i)
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
	{
		fireCount++;
		if (fireCount % 100 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				myMissile[i]->Fire(MissileManager::FIRETYPE::PlayerFIRE);
			}
			fireCount = 0;
		}
	}
}
