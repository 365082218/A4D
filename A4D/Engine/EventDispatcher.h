#pragma once
class Component;
class GameObject;
class Scene;
class Transform;
class EventDispatcher;
enum EventId
{
	All = 1,
	ComponentEnable = 10,
	ComponentDisable = 11,
	ActiveHierarchy = 12,
	InActiveHierarchy = 13,
	HierarchyChanged = 14,
	MeshChanged = 117,
	KeyUp = 201,
	KeyDown = 202,
	MouseUp = 203,
	MouseDown = 204,
	MouseMove = 205,
};

enum AEventType
{
	Remove = -1,//移除子节点.
	New = 0,//场景被创建.
	Add = 1,//添加子节点.
	Delete = 2,//场景卸载
};

class AEvent
{
public:
	AEvent();
	Component * pComponent;//组件
	GameObject * pGameObject;//对象
	Scene * pScene;//场景
};



class KeyEvent :public AEvent
{
public:
	unsigned int keyCode;
};

class HierarchyChangeEvent :public AEvent
{
public:
	AEventType type;//-1 remove 1 add
	Transform * transform;//
};

class MouseEvent :public AEvent
{
public:
	int mouseX;
	int mouseY;
};

typedef void(EventDispatcher::*LPHandler)(AEvent * context);

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
	void on(EventId evt, EventDispatcher* caller, LPHandler listener, bool once);
	void once(EventId evt, EventDispatcher* caller, LPHandler listener, AEvent * context);
	void off(EventId evt, EventDispatcher* caller, LPHandler listener, bool onceonly);
	void offAll(EventId evt = EventId::All);
	void fire(EventId evtId, AEvent * context);
	static void invoke(EventDispatcher * pDispatch, LPHandler method, AEvent * context);

	//组件消息
	virtual void OnEnable(AEvent * context);//组件enable
	virtual void OnDisable(AEvent * context);//组件disable
	virtual void OnMeshChanged(AEvent * context);//meshrender收到meshfilter改变了mesh
	virtual void OnActiveHierarchy(AEvent * context);//对象激活-gameobject-事件
	virtual void OnInActiveHierarchy(AEvent * context);//对象反激活-gameobject-事件
	virtual void OnHierarchyChanged(AEvent * context);//层级发生变化
	virtual void OnKeyDown(KeyEvent * context);
	virtual void OnKeyUp(KeyEvent * context);
	virtual void OnMouseDown(MouseEvent * context);
	virtual void OnMouseUp(MouseEvent * context);
	virtual void OnMouseMove(MouseEvent * context);
};

