#pragma once
#include "SceneManager.h"
class Subject
{
public:
	virtual void RegisterObserver(SceneManager* scenemanager) = 0;	
	virtual void UnRegisterObserver() = 0;
	virtual void notifyObserve() = 0;
};

