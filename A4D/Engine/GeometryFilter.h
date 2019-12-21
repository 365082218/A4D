#pragma once
#include "Component.h"
#include "Mesh.h"
//几何体过滤器
class GeometryFilter:public Component
{
public:
	GeometryFilter();
	~GeometryFilter();
	Mesh * _mesh;
	Mesh * _sharedMesh;
	virtual void Load(const char * path) = 0;
};

