#pragma once
#include "Observer.h"
#include "config.h"

enum BossNumber {
	oneBoss,twoBoss,threeBoss
};
class SceneManager :public Observer//�ɼ��� ������ �̿��� ���Ŵ���
{
private:
	
	Image* openingImage;
	Image* endingImage;
	int bossNumber = 0;
	int endingStatus = 2;
	bool endingTrue= false;
public:
	void Render(HDC hdc);
	
	virtual void DeadNotify(bool OneBossAlive, bool twoBossAlive, bool threeBossAlive);
	inline void SetBossNumber(int bossnumber) { this->bossNumber = bossnumber;	}
	inline int GetNextBoss() { return bossNumber; }
	inline int GetNextStatus() { return endingStatus; }
	inline bool GetEnding() { return endingTrue; }

};

