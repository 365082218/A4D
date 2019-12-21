#pragma once
#include "Layer.h"
#include "EventDispatcher.h"
#include "Transform.h"
#include "AObject.h"
class Layer;
class EventDispatcher;
class Transform;
class AObject;
class Component;
class GameObject:public AObject, public EventDispatcher
{
	
public:
	GameObject(std::string Name = "");
	~GameObject();
	std::list<Component*> components;
	void addComponent(Component * pCom);
	Component* addComponent(size_t id);
	Component* addComponent(std::string iden);
	Component * getComponent(size_t ComponentId);
	void RemoveComponent(size_t ComponentId);
	void RemoveComponent(Component * pCom);
	void _activeHierarchy(Event * context);
	void _inActiveHierarchy(Event * context);
	//void _addSelfRenderObjects();
	//void _clearSelfRenderObjects();
	Transform * transform;
	void OnPreRender();
	void OnPostRender();
	void update();
	void updateComponents();
	void lateUpdateComponents();
	Layer layer;
	bool isStatic;//ÊÇ·ñ¾²Ì¬Îï¼þ
	bool activeSelf;
	bool activeInHierarchy();
	Scene * m_pScene;
};

