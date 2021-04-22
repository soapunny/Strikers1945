#include "PlayerShip.h"
#include "Image.h"
#include "MissileManager.h"
#include "CommonFunction.h"
#include "CollisionCheck.h"

HRESULT PlayerShip::Init()
{
	return E_FAIL;
}

HRESULT PlayerShip::Init(CollisionCheck* collisionCheck)
{
	this->collisionCheck = collisionCheck;
	
	explosionimage = ImageManager::GetSingleton()->FindImage("��������");
	blinkImage = ImageManager::GetSingleton()->FindImage("�÷��̾� ������ ���ּ�");
	image = ImageManager::GetSingleton()->FindImage("�÷��̾� ���ּ�");
	retryImage = ImageManager::GetSingleton()->FindImage("�й迣��");
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
	reAppear = false;
	playerLife = 5;

	collisionSize.x = 35;
	collisionSize.y = 50;

	explosionCurrFrame = 0;
	blinkCount = 0;
	explosionCount=0;
	playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	collisionCheck->SetPlayerRect(playerRect);

	//����
	barrelSize = 1;
	barrelEnd[0] = { (pos.x - 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[1] = { (pos.x + 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[2] = { (pos.x + cosf(barrelAngle[2]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelEnd[3] = { (pos.x + cosf(barrelAngle[3]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelAngle[0] = PI / 2;
	barrelAngle[1] = PI / 2;
	barrelAngle[2] = 3 * (PI / 4);
	barrelAngle[3] = PI / 4;

	//�̻���
	for (int i = 0; i < 4; i++)
	{
		myMissile[i] = new MissileManager();
		myMissile[i]->Init(this->collisionCheck, barrelEnd[i]);
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
	float elapsedTime = TimerManager::GetSingleton()->getElapsedTime();

	playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	collisionCheck->SetPlayerRect(playerRect);

	//ù ���� (�Ʒ����� ����)
	if (!canMove)
	{
		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= elapsedTime * 500.0f;// 1.0f;
		else
			canMove = true;
	}

	if (playerLife <= 0)
	{
		isAlive = false;
	}

	//���ĺ���
	if (isAlive && KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))//�װ� �����ϸ� �����Ÿ�
	{
		isAlive = false;
		isDying = true;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown('H'))//�浹ó�� �÷��̾� ������ �����鼭 �ٽõ���
	{
		
	//	pos.x = WINSIZE_X / 2;
		//pos.y = WINSIZE_Y + 50;
		canMove = false;
		lifeDecrease = true;
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

	// ���� ��ġ, ������ ���� ��ǥ ���
	for (int i = 0; i < 2; i++)
	{
		barrelEnd[i] = { (pos.x - 10.0f + (20.0f * i)), (pos.y - barrelSize) };
	}

	for (int i = 2; i < 4; i++)
	{
		barrelEnd[i] = { ((pos.x - 10.0f + (20.0f * (i - 2))) + cosf(barrelAngle[i])* barrelSize) , pos.y - barrelSize };
	}

	for (int i = 0; i < 4; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->SetOwnerType(MissileManager::OWNERTYPE::Player);
			myMissile[i]->SetPlayerPos(this->pos);
			myMissile[i]->SetPos(barrelEnd[i]);
			myMissile[i]->SetAngle(barrelAngle[i]);
			myMissile[i]->Update();
			//����
			Attack(i);
		}
	}
	if (!isAlive)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('R')) //�׾����� �ٽý����Ұ��� ���� R�� ������ ����Ǵ� ������������ �״�� ����
		{
			playerLife = 5;
			isAlive = true;
		}
	}
}

void PlayerShip::Render(HDC hdc)
{
	//life ǥ��
	wsprintf(szText, "LIFE: %d",playerLife);
	TextOut(hdc, WINSIZE_X - 150, 80, szText, strlen(szText));

	//�̹���
	if (image)
	{
		if (reAppear == true)//�����̸� �ٽõ����ϱ� AlphaRender�� �������� ��� �� ���ľ��ҵ�
		{
			blinkImage->AlphaRender(hdc, pos.x, pos.y, true);//AlphaRender ���ĵ� �������� ����

			BLENDFUNCTION* blendFunc = blinkImage->GetBlendFunc();//�ϳ�¥�� �������� ����� �̹������°ɷ� ���� ����
			blinkCount++;
			if (blinkCount % 2 == 0)
			{
				blendFunc->SourceConstantAlpha = 0;
			}
			else
			{
				blendFunc->SourceConstantAlpha = 255;
			}

			if (blinkCount > 175)
			{
				blinkCount = 0;
				reAppear = false;
			}

		}
		else
		{

			if (isAlive)
			{
				image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
			}
			else //������ �ٽõ����Ҽ� �ִ� ȭ�� ����
			{
				retryImage->Render(hdc);

			}
		}
			//image->AlphaRender(hdc, pos.x, pos.y, true);
	}



	if (lifeDecrease == true )//�����̹��� ��ºκ�
	{	
		explosionCount++;
		if (explosionCount > 3)
		{
			explosionCurrFrame++; 
			explosionCount = 0;
		}
		
		explosionimage->FrameRender(hdc,pos.x, pos.y , explosionCurrFrame, 0, true);
		//explosionimage->FrameRender(hdc, pos.x, pos.y + 80, explosionCurrFrame, 0, true);
		if (explosionCurrFrame > 10)
		{
			canMove = false;
			pos.x = WINSIZE_X / 2;
			pos.y = WINSIZE_Y + 50;
		}
		if (explosionCurrFrame > 16)
		{
			explosionCurrFrame = 0;
			lifeDecrease = false;
			playerLife -= 1;
			reAppear = true;
			
			
		}
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

	//�̻���
	for (int i = 0; i < 4; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Render(hdc);
		}
	}
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
				myMissile[i]->Fire(FIRETYPE::PlayerFIRE);
			}
			fireCount = 0;
		}
	}
}
