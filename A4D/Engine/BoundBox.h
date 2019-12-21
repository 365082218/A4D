#pragma once
//AABB����
class BoundBox
{
public:
	BoundBox(D3DXVECTOR3 * min, D3DXVECTOR3 * max);
	~BoundBox();
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
	//��ȡ��Χ�е�8���Ƕ���.
	vector<D3DXVECTOR3> getCorners();
	vector<D3DXVECTOR3> corners;
	static BoundBox * createfromPoints(vector<D3DXVECTOR3> points);
	static BoundBox * merge(BoundBox * p0, BoundBox * p1);
};

