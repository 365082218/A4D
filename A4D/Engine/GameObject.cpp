#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "SkcRender.h"
#include "SceneManager.h"
#include "MeshFilter.h"
#include "SkcMeshFilter.h"

GameObject::GameObject(std::string Name):AObject(Name)
{
	transform = (Transform*)addComponent(typeid(Transform).hash_code());
	Scene * pActiveScene = SceneManager::GetActiveScene();
	pActiveScene->addChild(transform);
	m_pScene = pActiveScene;
	this->_activeHierarchy(NULL);
}

GameObject::~GameObject()
{

}

void GameObject::_activeHierarchy(Event * context)
{
	activeSelf = true;
	onevent(EventId::ComponentEnable, NULL);
	for (int i = 0, n = this->transform->m_pChild->size(); i < n; i++) {
		Transform* child = (Transform*)this->transform->m_pChild->at(i);
		if (child->gameObject->activeSelf)
			child->_activeHierarchy(NULL);
	}
}

bool GameObject::activeInHierarchy()
{
	if (this->transform->m_pParent == NULL)
		return this->activeSelf;
	Transform * trans = dynamic_cast<Transform*>(this->transform->m_pParent);
	return trans->gameObject->activeInHierarchy() && this->activeSelf;
}
bool _active;


void GameObject::_inActiveHierarchy(Event * context)
{
	_active = false;
	onevent(EventId::ComponentDisable, NULL);
	for (int i = 0, n = this->transform->m_pChild->size(); i < n; i++) {
		Transform* child = (Transform*)this->transform->m_pChild->at(i);
		if (child->gameObject->activeSelf)
			child->_inActiveHierarchy(NULL);
	}
}

Component * GameObject::addComponent(std::string iden)
{
	Component * pCom = static_cast<Component*>(CObjectFactory::createObjectByName(iden));
	addComponent(pCom);
	return pCom;
}

Component * GameObject::addComponent(size_t id)
{
	Component * pCom = static_cast<Component*>(CObjectFactory::createObjectById(id));
	addComponent(pCom);
	return pCom;
}

void GameObject::addComponent(Component * pCom)
{
	components.push_back(pCom);
	pCom->Awake(this);
	Event sender;
	sender.psender = pCom;
	onevent(EventId::ComponentEnable, &sender);
}

Component * GameObject::getComponent(size_t ComponentId)
{
	std::list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		Component * p = *it;
		if (p != NULL && p->type_id() == ComponentId)
		{
			return p;
		}
		it++;
	}
	return NULL;
}

void GameObject::RemoveComponent(size_t ComponentId)
{
	std::list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		Component * p = *it;
		if (p != NULL && p->type_id() == ComponentId)
		{
			components.erase(it);
			return;
		}
		it++;
	}
}

void GameObject::RemoveComponent(Component * com)
{
	std::list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		if ((*it) == com)
		{
			components.erase(it);
			return;
		}
		it++;
	}
}

void GameObject::OnPreRender()
{
	if (activeInHierarchy())
	{
		vector<Node*>::iterator it = transform->m_pChild->begin();
		for (; it != transform->m_pChild->end(); it++)
		{
			Transform * trans = dynamic_cast<Transform*>(*it);
			(trans->gameObject)->OnPreRender();
		}
	}
}

void GameObject::OnPostRender()
{
	if (activeInHierarchy())
	{
		vector<Node*>::iterator it = transform->m_pChild->begin();
		for (; it != transform->m_pChild->end(); it++)
		{
			Transform * trans = static_cast<Transform*>(*it);
			(trans->gameObject)->OnPostRender();
		}
	}
}

void GameObject::update()
{
	if (this->activeInHierarchy())
	{
		updateComponents();
		lateUpdateComponents();
	}
}

void GameObject::updateComponents()
{
	std::list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		Component * p = *it;
		if (p != NULL)
			p->Update();
		it++;
	}
}

void GameObject::lateUpdateComponents()
{
	std::list<Component*>::iterator it = components.begin();
	while (it != components.end())
	{
		Component * p = *it;
		if (p != NULL)
			p->LateUpdate();
		it++;
	}
}