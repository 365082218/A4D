#pragma once
#include "Component.h"
#include "Node.h"
class Node;
class GameObject;
class Transform:public Component, public Node
{
public:
	Transform()
	{
		D3DXMatrixIdentity(&localMatrix);
		D3DXMatrixIdentity(&_worldMatrix);
		worldUpdate = false;
	}
	void Awake(GameObject * pOwner);
	~Transform()
	{

	}

	D3DXMATRIX localMatrix;
	D3DXMATRIX _worldMatrix;
	bool worldUpdate;
	__inline D3DXMATRIX * worldMatrix()
	{
		if (worldUpdate)
		{
			Transform * pTransform = dynamic_cast<Transform*>(m_pParent);
			if (pTransform != NULL)
			{
				D3DXMatrixMultiply(&this->_worldMatrix, pTransform->worldMatrix(), &this->localMatrix);
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
				return &this->_worldMatrix;
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
				worldUpdate = false;
				return &_worldMatrix;
			}
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
			return &this->_worldMatrix;
		}
	}
	void Translate(D3DVECTOR vecTrans);
	void Translate(float x, float y, float z);
	void Rotate(D3DXVECTOR3 axis, float angle);
	void SetPosition(float x, float y, float z);
	void Scale(float x, float y, float z);
	void localUpdate();
	D3DXVECTOR3 position;
	D3DXVECTOR3 up;
	D3DXVECTOR3 forward;
	D3DXVECTOR3 right;
	__inline size_t type_id()
	{
		return typeid(Transform).hash_code();
	}
};

