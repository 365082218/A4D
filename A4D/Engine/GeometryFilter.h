#pragma once
#include "Component.h"
//�����������
class Mesh;
class GeometryFilter:public Component
{
public:
	GeometryFilter();
	~GeometryFilter();
	Mesh * _mesh;
	Mesh * _sharedMesh;
	virtual void Load(const char * path) = 0;
};

