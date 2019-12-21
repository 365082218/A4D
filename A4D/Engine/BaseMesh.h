#pragma once
#include "RenderState.h"
#include "Vector3.h"
#include "resources.h"
class BaseMesh: public Resource
{
public:
	virtual void _render(RenderState * rs) = 0;
	int subMeshCount;//子网格数量

	LPDIRECT3DTEXTURE9 * pTexture;
	BoundSphere * _boundingSphere;
	BoundBox * _boundingBox;

	vector<Vector3> position;
	/**
	*获取网格顶点,请重载此方法。
	*@return 网格顶点。
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
	*获取渲染单元数量,请重载此方法。
	*@return 渲染单元数量。
	*/
	virtual int getRenderElementsCount() {
		return 0;
	}

	/**
	*获取渲染单元,请重载此方法。
	*@param index 索引。
	*@return 渲染单元。
	*/
	virtual BaseMesh * getRenderElement(int index) {
		return NULL;
	}
};

