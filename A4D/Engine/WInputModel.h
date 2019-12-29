#pragma once
#include "EventDispatcher.h"
class InputMgr:public EventDispatcher
{
public:
	InputMgr();
	~InputMgr();
	void Init();
	void OnKeyDown(unsigned int key);
	void OnKeyUp(unsigned int key);
	bool IsKeyDown(unsigned int key);
private:
	bool key[256];
};

