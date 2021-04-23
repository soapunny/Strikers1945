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

	playerPower = 1;
	attackValue = 1;
	
	blinkImage = ImageManager::GetSingleton()->FindImage("�÷��̾� ������ ���ּ�");
	retryImage = ImageManager::GetSingleton()->FindImage("�й迣��");
	playerExplosion = ImageManager::GetSingleton()->FindImage("��������");
	playerExplosionStart = false;
	explosionCurrFrame = 0;
	explosionTime = 0.0f;
	blinkCount = 0;
	reAppear = false;
	
	//�÷��̾�
	image = ImageManager::GetSingleton()->FindImage("�÷��̾� ���ּ�");
	if (image == nullptr)
	{
		MessageBox(g_hWnd, "�÷��̾� ���ּ� �̹��� �ε� ����", "����", MB_OK);
		return E_FAIL;
	}
	currFrameX = 1;

	//����
	explosionImage = ImageManager::GetSingleton()->FindImage("���� ������ ���");
	if (explosionImage == nullptr)
	{
		MessageBox(g_hWnd, "���� ������ ��� �̹��� �ε� ����", "����", MB_OK);
		return E_FAIL;
	}
	currFrameX_ex = 0;
	imageTime = 0;
	bombUse = false;
	
	//����
	for (int i = 0; i < 5; i++)
	{
		lifeImg[i] = ImageManager::GetSingleton()->FindImage("����������ֱ�");
	}
	playerLife = 5;

	//��ź
	for (int i = 0; i < 3; i++)
	{
		bombImg[i] = ImageManager::GetSingleton()->FindImage("��ź����ֱ�");
	}
	bombNum = 3;

	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y + 50;

	moveSpeed = 300.0f;

	isAlive = true;
	//isDying = false;
	canMove = false;

	collisionSize.x = 35;
	collisionSize.y = 50;

	//playerRect = { (LONG)pos.x, (LONG)pos.y, (LONG)(pos.x + collisionSize.x), (LONG)(pos.y + collisionSize.y) };
	//collisionCheck->SetPlayerRect(playerRect);


	//����
	barrelSize = 1;
	
	barrelEnd[0] = { (pos.x - 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[1] = { (pos.x + 10.0f) ,  pos.y - barrelSize * 2 };
	barrelEnd[2] = { (pos.x + cosf(barrelAngle[2]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelEnd[3] = { (pos.x + cosf(barrelAngle[3]) * barrelSize) ,  pos.y - barrelSize * 2 };
	barrelEnd[4] = { (pos.x) ,  pos.y - barrelSize * 2 };

	barrelAngle[0] = PI / 2;
	barrelAngle[1] = PI / 2;
	barrelAngle[2] = 3 * (PI / 4);
	barrelAngle[3] = PI / 4;
	barrelAngle[4] = PI / 2;

	barrelAlive[0] = false;
	barrelAlive[1] = false;
	barrelAlive[2] = false;
	barrelAlive[3] = false;
	barrelAlive[4] = true;

	//�̻���
	for (int i = 0; i < 5; i++)
	{
		myMissile[i] = new MissileManager();
		if (barrelAlive[i])
			myMissile[i]->Init(this->collisionCheck, barrelEnd[i]);
		else
			myMissile[i]->Init(this->collisionCheck, {-100, -100});
	}
	fireTime = 0;

	return S_OK;
}

void PlayerShip::Release()
{
	for (int i = 0; i < 5; i++)
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

	//�浹
	playerRect = { (LONG)(pos.x - collisionSize.x / 3), (LONG)(pos.y - collisionSize.y / 3), (LONG)(pos.x + collisionSize.x / 3), (LONG)(pos.y + collisionSize.y / 3) };
	collisionCheck->SetPlayerRect(playerRect);

	//ù ���� (�Ʒ����� ����)
	if (!canMove && reAppear == false && playerExplosionStart == false)
	{
		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= elapsedTime * 250.0f;// 1.0f;
		else
			canMove = true;
	}
	else if(canMove && reAppear == false)
	{
		Move();
	}

	//�÷��̾� ������
	if (playerLife == 0)
	{
		//�����̹��� ���
		canMove = false;
		playerExplosionStart = true;
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

	for (int i = 4; i < 5; i++)
	{
		barrelEnd[i] = { (pos.x), (pos.y - barrelSize) };
	}

	for (int i = 0; i < 5; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->SetOwnerType(MissileManager::OWNERTYPE::Player);
			myMissile[i]->SetPlayerPos(this->pos); 
			if (barrelAlive[i])
				myMissile[i]->SetPos(barrelEnd[i]);
			myMissile[i]->SetAngle(barrelAngle[i]);
			myMissile[i]->SetPlayerPower(this->playerPower);
			myMissile[i]->Update();
			//����
			Attack(i);
		}
	}

	//�׾����� �ٽý����Ұ��� ���� R�� ������ ����Ǵ� ������������ �״�� ����
	if (!isAlive)
	{
		if (KeyManager::GetSingleton()->IsStayKeyDown('Y'))
		{
			pos.x = WINSIZE_X / 2;
			pos.y = WINSIZE_Y + 50;
			playerLife = 5;
			isAlive = true;
			reAppear = true;			//�����̸鼭 �ö���� ����  
		}
	}

	//�÷��̾� life �ִ� 5
	//if (playerLife >= 5)
	//{
	//	playerLife = 5;
	//}

	////��ź ���� �ִ� 3
	//if (bombNum >= 3)
	//{
	//	bombNum = 3;
	//}

	if (bombNum >= 1)
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown('X'))
		{
			bombNum -= 1;
			exPos = pos;
			tempSize = 0;
			bombUse = true;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		if (playerPower < 3)
			playerPower += 1;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('O'))
	{
		if (playerLife < 5)
			playerLife += 1;
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown('I'))
	{
		if (bombNum < 3)
			bombNum += 1;
	}
}

void PlayerShip::Render(HDC hdc)
{
	//life �׷��ֱ�
	if (playerLife >= 0)
	{
		for (int i = 0; i < playerLife; i++)
		{
			lifeImg[i]->Render(hdc, 30 + 45 * i, 40, true);
		}
	}
	//bomb �׷��ֱ�
	for (int i = 0; i < bombNum; i++)
	{
		bombImg[i]->Render(hdc, 30 + 45 * i, WINSIZE_Y - 40, true);
	}
	/*wsprintf(szText, "bomb: %d", bombNum);
	TextOut(hdc, WINSIZE_X - 150, 200, szText, strlen(szText));*/

	//�Ŀ� ǥ��
	wsprintf(szText, "Player Power: %d", playerPower);
	TextOut(hdc, WINSIZE_X - 150, 160, szText, strlen(szText));

	//�Ŀ� ǥ��
	wsprintf(szText, "Attack Value: %d", attackValue);
	TextOut(hdc, WINSIZE_X - 150, 180, szText, strlen(szText));

	//life ǥ��
	/*wsprintf(szText, "LIFE: %d",playerLife);
	TextOut(hdc, WINSIZE_X - 150, 80, szText, strlen(szText));*/

	//�̹���
	if (image)
	{
		if (isAlive && reAppear == false)
		{
			image->FrameRender(hdc, pos.x, pos.y, currFrameX, 0, true);
		}
		else //������ �ٽõ����Ҽ� �ִ� ȭ�� ����
		{
			playerExplosionStart = false;
			//retryImage->Render(hdc);
		}
		//image->AlphaRender(hdc, pos.x, pos.y, true);
	}

	//�����̹��� ��ºκ�
	if (playerExplosionStart && reAppear == false)
	{
		playerExplosion->FrameRender(hdc, pos.x, pos.y, explosionCurrFrame, 0, true);

		explosionTime += 1.0f;
		if (explosionTime > 5.0f)
		{
			explosionCurrFrame++;
			explosionTime = 0.0f;
		}

		if (explosionCurrFrame >= 16)	//���� �̹��� ����
		{
			explosionCurrFrame = 0;
			explosionTime = 0.0f;
			isAlive = false;			//������
			playerExplosionStart = false;
		}
	}

	//�����̸� �ٽõ����ϱ� AlphaRender�� �������� ��� �� ���ľ��ҵ�
	if (reAppear == true)
	{
		playerLife = 5;

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

		if (pos.y >= WINSIZE_Y - 200)
			pos.y -= TimerManager::GetSingleton()->getElapsedTime() * 250.0f;// 1.0f;

		else
		{
			blinkCount = 0;
			reAppear = false;
			canMove = true;
		}
	}

	// ����
	if (playerPower == 1)
	{
		MoveToEx(hdc, pos.x, pos.y, NULL);
		LineTo(hdc, barrelEnd[4].x, barrelEnd[4].y);
	}
	if (playerPower >= 2)
	{
		barrelAlive[4] = false;
		barrelEnd[4] = { -100, -100 };

		barrelAlive[0] = true;
		barrelAlive[1] = true;

		MoveToEx(hdc, pos.x - 10, pos.y, NULL);
		LineTo(hdc, barrelEnd[0].x, barrelEnd[0].y);

		MoveToEx(hdc, pos.x + 10, pos.y, NULL);
		LineTo(hdc, barrelEnd[1].x, barrelEnd[1].y);

		if (playerPower >= 3)
		{
			barrelAlive[2] = true;
			barrelAlive[3] = true;

			MoveToEx(hdc, pos.x - 10, pos.y, NULL);
			LineTo(hdc, barrelEnd[2].x, barrelEnd[2].y);

			MoveToEx(hdc, pos.x + 10, pos.y, NULL);
			LineTo(hdc, barrelEnd[3].x, barrelEnd[3].y);
		}
	}

	//�̻���
	for (int i = 0; i < 5; i++)
	{
		if (myMissile[i])
		{
			myMissile[i]->Render(hdc);
		}
	}

	//���� ������ ���/////////////////////////////////////
	if (bombUse)
	{
		if (currFrameX_ex < 5)
			tempSize = 30 * currFrameX_ex;
		else
			tempSize = 150;

		bombRect = { (LONG)(exPos.x - tempSize), (LONG)((exPos.y - 150) - tempSize),
		(LONG)(exPos.x + tempSize), (LONG)((exPos.y - 150) + tempSize) };
		collisionCheck->SetBombRect(bombRect);

		explosionImage->FrameRender(hdc, exPos.x, exPos.y - 150, currFrameX_ex, 0, true);

		imageTime += TimerManager::GetSingleton()->getElapsedTime();
		if (imageTime > 0.1f)
		{
			if (currFrameX_ex < 12)
				currFrameX_ex++;
			else
			{
				currFrameX_ex = 0;
				bombUse = false;
				//
			}
			imageTime = 0;
		}
	}

	(this->collisionCheck)->SetBombUse(this->bombUse);
}

void PlayerShip::Move()
{
	if (canMove)
	{
		currFrameX = 1;
		collisionSize.x = 35;

		if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
		{
			collisionSize.x = 22;
			currFrameX = 0;
			if (pos.x > 20)
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
}

void PlayerShip::Attack(int i)
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('Z') && canMove)
	{
		fireTime += TimerManager::GetSingleton()->getElapsedTime();
		if (fireTime > 0.5f)
		{
			for (int i = 0; i < 5; i++)
			{
				if(barrelAlive[i])
					myMissile[i]->Fire(FIRETYPE::PlayerFIRE);
			}
			fireTime = 0;
		}
	}
}
