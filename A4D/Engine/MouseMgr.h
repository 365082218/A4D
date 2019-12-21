#pragma once
#include "EventDispatcher.h"
class MouseMgr :
	public EventDispatcher
{
public:
	MouseMgr();
	~MouseMgr();
	vector<MouseEvent> eventList;
	void update();
	bool check();
	bool enable;
};

