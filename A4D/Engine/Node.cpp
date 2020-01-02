#include "stdafx.h"
#include "Node.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "Transform.h"
#include "Scene.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "TexturePool.h"
#include "WInputModel.h"
#include "Console.h"
#include "Pool.h"
#include "Time.h"
#include "MouseMgr.h"
#include "WGraphics.h"
#include "../A4D.h"

Node::Node()
{
	m_pChild = new std::vector<Node*>;
	m_strName = "";
	m_pParent = NULL;
}


Node::~Node()
{
}

void Node::addChild(Node * child)
{
	if (child == NULL)
		return;
	if (child->m_pParent == this)
	{
		MessageBox(0, _T("addChild already Exist"), _T("Error"), MB_OK);
		return;
	}
	m_pChild->push_back(dynamic_cast<Transform*>(child));
	child->setParent(dynamic_cast<Transform*>(this));
#if (EngineEditor)
	HierarchyChangeEvent evt;
	evt.pComponent = dynamic_cast<Transform*>(this);
	evt.pGameObject = dynamic_cast<Transform*>(evt.pComponent)->gameObject;
	evt.pScene = evt.pGameObject->m_pScene;
	evt.transform = dynamic_cast<Transform*>(child);
	evt.type = AEventType::Add;
	A4D::getInstance()->fire(EventId::HierarchyChanged, &evt);
#endif
}

void Node::setParent(Node * parent)
{
	m_pParent = dynamic_cast<Transform*>(parent);
}

void Node::setSiblingIndex(Node * pChild, int index)
{

}

void Node::setAsFirstSibling(Node * pNode)
{

}

void Node::setAsLastSibling(Node * pNode)
{

}


