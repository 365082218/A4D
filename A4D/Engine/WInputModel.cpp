#include "stdafx.h"
#include "EventDispatcher.h"
#include "WInputModel.h"


InputMgr::InputMgr()
{
}


InputMgr::~InputMgr()
{
}

void InputMgr::Init()
{
	for (int i = 0; i < 256; i++)
		key[i] = false;
}

void InputMgr::OnKeyDown(unsigned int keyCode)
{
	if (keyCode > 255)
	{
		MessageBox(NULL, _T("123"), _T("123"), MB_OK);
		return;
	}
	key[keyCode] = true;
	KeyEvent context;
	context.keyCode = keyCode;
	context.pComponent = NULL;
	context.pGameObject = NULL;
	context.pScene = NULL;
	this->fire(EventId::KeyDown, &context);
}

void InputMgr::OnKeyUp(unsigned int keyCode)
{
	key[keyCode] = false;
	KeyEvent context;
	context.keyCode = keyCode;
	context.pComponent = NULL;
	context.pGameObject = NULL;
	context.pScene = NULL;
	this->fire(EventId::KeyUp, &context);
}

bool InputMgr::IsKeyDown(unsigned int keyCode)
{
	return key[keyCode];
}