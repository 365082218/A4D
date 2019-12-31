#include "stdafx.h"
#include "CameraMove.h"
#include <QtGui/qevent.h>
#include <d3d9.h>
#include <d3dx9tex.h>
#include "Pool.h"
#include "Time.h"
#include "GameObject.h"
#include "Transform.h"
//��������ƽű�

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
	//6�������ƽ��
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

	//3���������ת
	if (context->keyCode == Qt::Key_R)
		gameObject->transform->Rotate(D3DXVECTOR3(0, 1, 0), Time::deltaTime * intensity);//��Y��
	if (context->keyCode == Qt::Key_T)
		gameObject->transform->Rotate(D3DXVECTOR3(1, 0, 0), Time::deltaTime * intensity);//��X��
	if (context->keyCode == Qt::Key_Y)
		gameObject->transform->Rotate(D3DXVECTOR3(0, 0, 1), Time::deltaTime * intensity);//��Z��
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

void CameraMove::OnEnable(AEvent * context)
{
	__super::OnEnable(context);
}

void CameraMove::OnDisable(AEvent * context)
{
	__super::OnDisable(context);
}