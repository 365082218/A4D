#include "stdafx.h"
#include "RenderElement.h"
#include "Render.h"
#include "Node.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "GameObject.h"
#include "Transform.h"
#include "BaseMesh.h"
RenderElement::RenderElement()
{
	_staticBatch = NULL;
}


RenderElement::~RenderElement()
{
}
