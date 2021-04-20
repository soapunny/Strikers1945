#pragma once

class Observer
{
public:
	virtual void DeadNotify(bool OneBossAlive, bool twoBossAlive, bool threeBossAlive) = 0;
};

