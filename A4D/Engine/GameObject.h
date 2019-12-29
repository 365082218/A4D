#pragma once
#include "AObject.h"
#include "EventDispatcher.h"
class Layer;
class Scene;
class Transform;
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
	void ActiveHierarchy();//激活此层级.
	void InActiveHierarchy();//反激活此层级.
	//void _addSelfRenderObjects();
	//void _clearSelfRenderObjects();
	Transform * transform;
	void OnPreRender();
	void OnPostRender();
	void update();
	
	Layer * layer;
	bool isStatic;//是否静态物件
	bool activeSelf;//自身是否激活
	bool activeInHierarchy;//层级递归后是否激活
	Scene * m_pScene;
protected:
	void updateComponents();
	void lateUpdateComponents();
};

