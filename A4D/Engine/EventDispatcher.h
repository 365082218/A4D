#pragma once
#include <map>
#include <vector>
using namespace std;
class EventDispatcher;
class Component;
class Event;
class InputMgr;
typedef void(EventDispatcher::*LPHandler)(Event * context);
enum EventId
{
	All = 1,
	ComponentEnable = 10,
	ComponentDisable = 11,
	MeshChanged = 117,
	KeyUp = 201,
	KeyDown = 202,
	MouseUp = 203,
	MouseDown = 204,
	MouseMove = 205,
};

class Event
{
public:
	Component * psender;
};

class KeyEvent :public Event
{
public:
	unsigned int keyCode;
};

class MouseEvent :public Event
{
public:
	int mouseX;
	int mouseY;
};

class EventHandler
{
public:
	EventDispatcher * caller;
	LPHandler listener;
	bool once;
};

class EventDispatcher
{
public:
	EventDispatcher();
	~EventDispatcher();
	map<int, vector<EventHandler*>*> _events;
	void on(EventId evt, EventDispatcher* caller, LPHandler listener, Event * context, bool once);
	void once(EventId evt, EventDispatcher* caller, LPHandler listener, Event * context);
	void off(EventId evt, EventDispatcher* caller, LPHandler listener, bool onceonly);
	void offAll(EventId evt = EventId::All);
	void onevent(EventId evtId, Event * context);
	static void invoke(EventDispatcher * pDispatch, LPHandler method, Event * context);

	//组件消息
	virtual void OnEnable(Event * context);//组件enable
	virtual void OnDisable(Event * context);//组件disable
	virtual void OnMeshChanged(Event * context);//meshrender收到meshfilter改变了mesh
	virtual void _activeHierarchy(Event * context);//对象激活-gameobject
	virtual void _inActiveHierarchy(Event * context);//对象反激活-gameobject
	virtual void OnKeyDown(KeyEvent * context);
	virtual void OnKeyUp(KeyEvent * context);
	virtual void OnMouseDown(MouseEvent * context);
	virtual void OnMouseUp(MouseEvent * context);
	virtual void OnMouseMove(MouseEvent * context);
};

