#include "StdAfx.h"
#include "Time.h"

float Time::deltaTime = 0;
int Time::frame = 0;
TimerHandler::TimerHandler()
{
	
}

TimerHandler::~TimerHandler()
{

}

void TimerHandler::update(int mill)
{
	if (tick - mill <= 0)
	{
		this->pfn();
		tick = milliseconds;
	}
	else
		tick -= mill;
}

Time::Time()
{

}

Time::~Time()
{

}

void Time::update()
{
	frame++;
}