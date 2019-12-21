#pragma once
#include <vector>
#include "EventDispatcher.h"
using namespace std;
class Scene;
class EventDispatcher;
class Node
{
public:
	Node();
	~Node();
	void addChild(Node * child);
	virtual void setParent(Node * parent);
	void setSiblingIndex(Node * pChild, int index);
	void setAsFirstSibling(Node * pNode);
	void setAsLastSibling(Node * pNode);
	std::string m_strName;
	std::vector<Node*> * m_pChild;
	Node * m_pParent;
};

