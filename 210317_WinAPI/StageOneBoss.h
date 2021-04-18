#include "GameNode.h"
#include "Boss.h"

class StageOneBoss : public Boss
{
private:

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual void Attack();
	virtual void Move();
	virtual void RotateBarrel(float angle);
	virtual void OnDead();
};
