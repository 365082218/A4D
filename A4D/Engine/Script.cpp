#include "stdafx.h"
#include "Script.h"


Script::Script()
{
}


Script::~Script()
{
}

void Script::OnEnable(Event * context)
{
	A4D::getInstance()->pInput->on(EventId::KeyDown, this, (LPHandler)&Component::OnKeyDown, NULL, false);
	A4D::getInstance()->pInput->on(EventId::KeyUp, this, (LPHandler)&Component::OnKeyUp, NULL, false);
}

void Script::OnDisable(Event * context)
{
	A4D::getInstance()->pInput->off(EventId::KeyDown, this, (LPHandler)&Component::OnKeyDown, false);
	A4D::getInstance()->pInput->off(EventId::KeyUp, this, (LPHandler)&Component::OnKeyUp, false);
}

//meshrenderer¹ØÐÄ
void Script::OnMeshChanged(Event * context)
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