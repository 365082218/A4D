#include "stdafx.h"
#include "CameraMove.h"
#include "object.h"

//摄像机控制脚本
REGISTER_CLASS(CameraMove)
CameraMove::CameraMove()
{
	intensity = 5;
}


CameraMove::~CameraMove()
{
}



void CameraMove::Update()
{
	
}

void CameraMove::OnKeyDown(KeyEvent * context)
{
	//6个方向的平移
	if (context->keyCode == Qt::Key_W)
	{
		D3DXVECTOR3 vec = gameObject->transform->forward * Time::deltaTime * intensity;
		gameObject->transform->Translate(vec);
	}

	if (context->keyCode == Qt::Key_S)
	{
		D3DXVECTOR3 vec = gameObject->transform->forward * -Time::deltaTime * intensity;
		gameObject->transform->Translate(vec);
	}

	if (context->keyCode == Qt::Key_A)
		gameObject->transform->Translate(-intensity * Time::deltaTime, 0, 0);
	if (context->keyCode == Qt::Key_D)
		gameObject->transform->Translate(intensity * Time::deltaTime, 0, 0);
	if (context->keyCode == Qt::Key_E)
		gameObject->transform->Translate(0, intensity * Time::deltaTime, 0);
	if (context->keyCode == Qt::Key_Q)
		gameObject->transform->Translate(0, -intensity * Time::deltaTime, 0);

	//3个轴向的旋转
	if (context->keyCode == Qt::Key_R)
		gameObject->transform->Rotate(D3DXVECTOR3(0, 1, 0), Time::deltaTime * intensity);//绕Y轴
	if (context->keyCode == Qt::Key_T)
		gameObject->transform->Rotate(D3DXVECTOR3(1, 0, 0), Time::deltaTime * intensity);//绕X轴
	if (context->keyCode == Qt::Key_Y)
		gameObject->transform->Rotate(D3DXVECTOR3(0, 0, 1), Time::deltaTime * intensity);//绕Z轴
}

void CameraMove::OnKeyUp(KeyEvent * context)
{

}

void CameraMove::OnMouseDown(MouseEvent * context)
{

}

void CameraMove::OnMouseUp(MouseEvent * context)
{

}

void CameraMove::OnEnable(Event * context)
{
	__super::OnEnable(context);
}

void CameraMove::OnDisable(Event * context)
{
	__super::OnDisable(context);
}