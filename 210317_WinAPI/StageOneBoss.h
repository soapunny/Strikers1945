#include "Boss.h"
#include "MoveInterface.h"

class StageOneBoss : public Boss
{
private:
	vector<MoveInterface*> vMoveInterfaces; 
	MoveInterface* currMoveInterface;
	float time;
	char szText[128];

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Attack();
	virtual void OnDead();
	void Move();
};
