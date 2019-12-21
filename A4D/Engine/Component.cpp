#include "stdafx.h"
#include "Component.h"
#include "object.h"

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
	pOwner->on(EventId::ComponentEnable, this, (LPHandler)&Component::OnEnable, NULL, false);
	pOwner->on(EventId::ComponentDisable, this, (LPHandler)&Component::OnDisable, NULL, false);
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

void Component::OnEnable(Event * context)
{

}

void Component::OnDisable(Event * context)
{

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