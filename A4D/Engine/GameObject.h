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
	void ActiveHierarchy();//����˲㼶.
	void InActiveHierarchy();//������˲㼶.
	//void _addSelfRenderObjects();
	//void _clearSelfRenderObjects();
	Transform * transform;
	void OnPreRender();
	void OnPostRender();
	void update();
	
	Layer * layer;
	bool isStatic;//�Ƿ�̬���
	bool activeSelf;//�����Ƿ񼤻�
	bool activeInHierarchy;//�㼶�ݹ���Ƿ񼤻�
	Scene * m_pScene;
protected:
	void updateComponents();
	void lateUpdateComponents();
};

