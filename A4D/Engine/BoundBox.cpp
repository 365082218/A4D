#include "stdafx.h"
#include "BoundBox.h"


BoundBox::BoundBox(D3DXVECTOR3 * min, D3DXVECTOR3 * max)
{
}


BoundBox::~BoundBox()
{
}

vector<D3DXVECTOR3> BoundBox::getCorners()
{
	return corners;
}

BoundBox * BoundBox::createfromPoints(vector<D3DXVECTOR3> points)
{
	return NULL;
}

BoundBox * BoundBox::merge(BoundBox * p0, BoundBox * p1)
{
	return NULL;
}