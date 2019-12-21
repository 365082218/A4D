#pragma once
#include <map>
#include "Pool.h"
#define _MAX_TIMER 50
using namespace std;
typedef int (* LPFNTimeFunction)(void);
class TimerHandler
{
public:
	TimerHandler();
	~TimerHandler();
	int id;
	int milliseconds;//¼ä¸ô
	int tick;//¼ÆÊ±
	void update(int mill);
	LPFNTimeFunction pfn;
};

class Time
{
public:
	Time();
	~Time();
	std::map<int, TimerHandler*> _map;
	Pool<TimerHandler> * pool;
	static float deltaTime;
	static int frame;
	void update();
};

