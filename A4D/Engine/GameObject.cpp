#include "stdafx.h"
#include "Node.h"
#include "GameObject.h"
#include "EventDispatcher.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
GameObject::GameObject(std::string Name):AObject(Name)
{
	m_pScene = NULL;
	transform = (Transform*)addComponent(typeid(Transform).hash_code());
	Scene * pActiveScene = SceneManager::GetActiveScene();
	pActiveScene->addChild(this);
	m_pScene = pActiveScene;
	activeSelf = true;
	activeInHierarchy = true;
}

GameObject::~GameObject()
{

}

void GameObject::ActiveHierarchy()
{
	if (this->transform->m_pParent != NULL)
		activeInHierarchy = activeSelf && ((Transform*)this->transform->m_pParent)->gameObject->activeInHierarchy;
	else
		activeInHierarchy = activeSelf;
	if (activeInHierarchy)
	{
		for (int i = 0, n = this->transform->m_pChild->size(); i < n; i++) {
			Transform* child = (Transform*)this->transform->m_pChild->at(i);
			if (child->gameObject->activeSelf)
				child->gameObject->ActiveHierarchy();
		}
	}
}

void GameObject::InActiveHierarchy()
{
	if (this->transform->m_pParent != NULL)
		activeInHierarchy = activeSelf && ((Transform*)this->transform->m_pParent)->gameObject->activeInHierarchy;
	else
		activeInHierarchy = activeSelf;
	if (!activeInHierarchy)
	{
		for (int i = 0, n = this->transform->m_pChild->size(); i < n; i++) {
			Transform* child = (Transform*)this->transform->m_pChild->at(i);
			if (child->gameObject->activeSelf)
				child->gameObject->InActiveHierarchy();
		}
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
	AEvent sender;
	sender.pComponent = pCom;
	sender.pGameObject = this;
	sender.pScene = this->m_pScene;
	fire(EventId::ComponentEnable, &sender);
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
	if (activeInHierarchy)
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
	if (activeInHierarchy)
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
	if (activeInHierarchy)
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