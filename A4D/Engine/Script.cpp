#include "stdafx.h"
#include "Script.h"
#include "EventDispatcher.h"
#include "GameWorld.h"
#include "TexturePool.h"
#include "WInputModel.h"
#include "Console.h"
#include "Pool.h"
#include "Time.h"
#include "MouseMgr.h"
#include "WGraphics.h"
#include "GameObject.h"
#include "Transform.h"
#include "../A4D.h"
#include "Scene.h"
Script::Script()
{
}


Script::~Script()
{
}

void Script::OnEnable(AEvent * context)
{
	A4D::getInstance()->pInput->on(EventId::KeyDown, this, (LPHandler)&Component::OnKeyDown, false);
	A4D::getInstance()->pInput->on(EventId::KeyUp, this, (LPHandler)&Component::OnKeyUp, false);
}

void Script::OnDisable(AEvent * context)
{
	A4D::getInstance()->pInput->off(EventId::KeyDown, this, (LPHandler)&Component::OnKeyDown, false);
	A4D::getInstance()->pInput->off(EventId::KeyUp, this, (LPHandler)&Component::OnKeyUp, false);
}

//meshrenderer¹ØÐÄ
void Script::OnMeshChanged(AEvent * context)
{

}

void Script::OnKeyDown(KeyEvent * context)
{

}

void Script::OnKeyUp(KeyEvent * context)
{

}

void Script::OnMouseDown(MouseEvent * context)
{

}

void Script::OnMouseUp(MouseEvent * context)
{

}

void Script::OnMouseMove(MouseEvent * context)
{

}