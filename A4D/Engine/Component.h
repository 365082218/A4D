#pragma once
class GameObject;
class EventDispatcher;
class Component:public EventDispatcher
{
protected:
	Component();
public:
	~Component();
	virtual void Awake(GameObject * pOwner);//自身被加入到GameObject上
	virtual size_t type_id() = 0;
	void addComponent(Component * pCom);
	Component * getComponent(size_t ComponentId);
	void removeComponent(Component * pCom);
	void removeComponent(size_t ComponentId);
	virtual void OnEnable(Event * context);
	virtual void OnDisable(Event * context);
	virtual void PreUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void FixUpdate();
	std::list<Component*> * components;
	GameObject * gameObject;
	bool enable;
};