#include "stdafx.h"
#include "Node.h"


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


