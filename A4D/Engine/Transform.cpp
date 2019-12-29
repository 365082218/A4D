#include "stdafx.h"
#include "Node.h"
#include "transform.h"
#include <d3dx9tex.h>
#include "Component.h"
#include "EventDispatcher.h"
REGISTER_CLASS(Transform)
void Transform::SetPosition(float x, float y, float z)
{
	localMatrix._41 = x;
	localMatrix._42 = y;
	localMatrix._43 = z;
	worldUpdate = true;
	localUpdate();
}

void Transform::localUpdate()
{
	if (worldUpdate)
	{
		Transform * trans = dynamic_cast<Transform*>(m_pParent);
		if (trans != NULL)
		{
			D3DXMatrixMultiply(&this->_worldMatrix, trans->worldMatrix(), &this->localMatrix);
			worldUpdate = false;
			position.x = this->_worldMatrix._41;
			position.y = this->_worldMatrix._42;
			position.z = this->_worldMatrix._43;
			right.x = this->_worldMatrix._11;
			right.y = this->_worldMatrix._12;
			right.z = this->_worldMatrix._13;
			up.x = this->_worldMatrix._21;
			up.y = this->_worldMatrix._22;
			up.z = this->_worldMatrix._23;
			forward.x = this->_worldMatrix._31;
			forward.y = this->_worldMatrix._32;
			forward.z = this->_worldMatrix._33;
		}
		else
		{
			memcpy(&_worldMatrix, &localMatrix, sizeof(localMatrix));
			position.x = this->_worldMatrix._41;
			position.y = this->_worldMatrix._42;
			position.z = this->_worldMatrix._43;
			right.x = this->_worldMatrix._11;
			right.y = this->_worldMatrix._12;
			right.z = this->_worldMatrix._13;
			up.x = this->_worldMatrix._21;
			up.y = this->_worldMatrix._22;
			up.z = this->_worldMatrix._23;
			forward.x = this->_worldMatrix._31;
			forward.y = this->_worldMatrix._32;
			forward.z = this->_worldMatrix._33;
		}
		worldUpdate = false;
	}
	else
	{
		position.x = this->_worldMatrix._41;
		position.y = this->_worldMatrix._42;
		position.z = this->_worldMatrix._43;
		right.x = this->_worldMatrix._11;
		right.y = this->_worldMatrix._12;
		right.z = this->_worldMatrix._13;
		up.x = this->_worldMatrix._21;
		up.y = this->_worldMatrix._22;
		up.z = this->_worldMatrix._23;
		forward.x = this->_worldMatrix._31;
		forward.y = this->_worldMatrix._32;
		forward.z = this->_worldMatrix._33;
	}
}

void Transform::Awake(GameObject * pOwner)
{
	__super::Awake(pOwner);
	m_pParent = NULL;
	m_pChild->clear();
}

void Transform::Translate(D3DVECTOR vecTrans)
{
	Translate(vecTrans.x, vecTrans.y, vecTrans.z);
}

void Transform::Translate(float x, float y, float z)
{
	localMatrix._41 += x;
	localMatrix._42 += y;
	localMatrix._43 += z;
	worldUpdate = true;
	localUpdate();
}

void Transform::Rotate(D3DXVECTOR3 axis, float angle)
{
	D3DXMATRIX matrix;
	//D3DXMatrixRotationY(&matrix, angle);
	D3DXMatrixRotationAxis(&matrix, &axis, angle);
	localMatrix *= matrix;
	worldUpdate = true;
	localUpdate();
}

void Transform::Scale(float x, float y, float z)
{
	D3DXMatrixScaling(&localMatrix, x, y, z);
	worldUpdate = true;
	localUpdate();
}