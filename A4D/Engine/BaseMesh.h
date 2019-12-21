#pragma once
#include "RenderState.h"
#include "Vector3.h"
#include "resources.h"
class BaseMesh: public Resource
{
public:
	virtual void _render(RenderState * rs) = 0;
	int subMeshCount;//����������

	LPDIRECT3DTEXTURE9 * pTexture;
	BoundSphere * _boundingSphere;
	BoundBox * _boundingBox;

	vector<Vector3> position;
	/**
	*��ȡ���񶥵�,�����ش˷�����
	*@return ���񶥵㡣
	*/
	virtual void getPositions() {}

	/**
	*@private
	*/
	virtual void generateBoundingObject() {
		//_boundingSphere = new BoundSphere(new Vector3(), 0);
		//BoundSphere::createfromPoints(_positions, _boundingSphere);
		//_boundingBox = new BoundBox(new Vector3(), new Vector3());
		//BoundBox::createfromPoints(_positions, _boundingBox);
		//this._boundingBox.getCorners(this._boundingBoxCorners);
	}

	/**
	*��ȡ��Ⱦ��Ԫ����,�����ش˷�����
	*@return ��Ⱦ��Ԫ������
	*/
	virtual int getRenderElementsCount() {
		return 0;
	}

	/**
	*��ȡ��Ⱦ��Ԫ,�����ش˷�����
	*@param index ������
	*@return ��Ⱦ��Ԫ��
	*/
	virtual BaseMesh * getRenderElement(int index) {
		return NULL;
	}
};

