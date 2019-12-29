#include "stdafx.h"
#include "EventDispatcher.h"
AEvent::AEvent()
{

}

EventDispatcher::EventDispatcher()
{
}


EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::fire(EventId evtId, AEvent * context)
{
	map<int, vector<EventHandler*>*>::iterator listeners = _events.find(evtId);
	if (listeners != _events.end())
	{
		vector<EventHandler*>::iterator listener = listeners->second->begin();
		while (listener != listeners->second->end())
		{
			EventHandler * pHandler = *listener;
			invoke(pHandler->caller, pHandler->listener, context);
			if (pHandler->once)
			{
				listener = listeners->second->erase(listener);
				continue;
			}
			listener++;
		}
	}
	else
	{

	}
}

void EventDispatcher::offAll(EventId evt)
{
	//内存暂时不处理.
	OutputDebugString(_T("memory leak"));
	if (evt == EventId::All)
	{
		_events.clear();
	}
	else
	{
		map<int, vector<EventHandler*>*>::iterator it = _events.find(evt);
		if (it != _events.end())
		{
			_events.erase(it);
		}
	}
}

void EventDispatcher::on(EventId evtId, EventDispatcher* caller, LPHandler listener, bool once)
{
	map<int, vector<EventHandler*>*>::iterator it = _events.find(evtId);
	if (it != _events.end())
	{
		//找到同一个监听者
		vector<EventHandler*>::iterator listeners = it->second->begin();
		while (listeners != it->second->end())
		{
			if ((*listeners)->caller == caller)
			{
				//如果已经监听此事件，覆盖
				(*listeners)->listener = listener;
				(*listeners)->once = once;
				return;
			}
			listeners++;
		}

		//没有找到同一个监听者
		EventHandler * handler = new EventHandler();
		handler->caller = caller;
		handler->listener = listener;
		handler->once = once;
		it->second->push_back(handler);
	}
	else
	{
		vector<EventHandler*> * msgQueue = new vector<EventHandler*>();
		EventHandler * handler = new EventHandler();
		handler->caller = caller;
		handler->listener = listener;
		handler->once = once;
		msgQueue->push_back(handler);
		_events.insert(pair<int, vector<EventHandler*>*>(evtId, msgQueue));
	}
}

void EventDispatcher::once(EventId evt, EventDispatcher* caller, LPHandler listener, AEvent * context)
{

}

void EventDispatcher::off(EventId evt, EventDispatcher* caller, LPHandler listener, bool onceonly)
{

}

void EventDispatcher::invoke(EventDispatcher * pDispatch, LPHandler method, AEvent * context)
{
	auto b = std::bind(method, pDispatch, context);
	b();
}

void EventDispatcher::OnEnable(AEvent * context)
{

}

void EventDispatcher::OnDisable(AEvent * context)
{

}

void EventDispatcher::OnMeshChanged(AEvent * context)
{

}

void EventDispatcher::OnActiveHierarchy(AEvent * context)
{

}

void EventDispatcher::OnInActiveHierarchy(AEvent * context)
{

}
void EventDispatcher::OnHierarchyChanged(AEvent * context)
{

}

void EventDispatcher::OnKeyDown(KeyEvent * context)
{

}

void EventDispatcher::OnKeyUp(KeyEvent * context)
{

}

void EventDispatcher::OnMouseDown(MouseEvent * context)
{

}

void EventDispatcher::OnMouseUp(MouseEvent * context)
{

}

void EventDispatcher::OnMouseMove(MouseEvent * context)
{

}