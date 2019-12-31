#include "stdafx.h"
#include "GameObject.h"
#include "EventDispatcher.h"
#include "Component.h"

Component::Component()
{
	enable = true;
}

Component::~Component()
{

}

void Component::Awake(GameObject * pOwner)
{
	gameObject = pOwner;
	components = &pOwner->components;
	pOwner->on(EventId::ComponentEnable, this, (LPHandler)&Component::OnEnable, false);
	pOwner->on(EventId::ComponentDisable, this, (LPHandler)&Component::OnDisable, false);
}

void Component::addComponent(Component * pCom)
{
	if (pCom == NULL || components == NULL)
		return;
	//对pcom来说，其他组件激活了，对其他组件来说pcom组件激活了
	gameObject->addComponent(pCom);
}

Component * Component::getComponent(size_t ComponentId)
{
	return gameObject->getComponent(ComponentId);
}

void Component::removeComponent(Component * pCom)
{
	gameObject->RemoveComponent(pCom);
}

void Component::removeComponent(size_t ComponentId)
{
	gameObject->RemoveComponent(ComponentId);
}

void Component::OnEnable(AEvent * context)
{
	enable = true;
}

void Component::OnDisable(AEvent * context)
{
	enable = false;
}

void Component::Update()
{

}

void Component::PreUpdate()
{

}

void Component::LateUpdate()
{

}

void Component::FixUpdate()
{

}