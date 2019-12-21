#pragma once
//包围球，中心位置+半径
class BoundSphere
{
public:
	BoundSphere();
	~BoundSphere();
	D3DXVECTOR3 center;
	float radius;
};

