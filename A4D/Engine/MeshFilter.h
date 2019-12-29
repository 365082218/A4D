#pragma once
#include "GeometryFilter.h"
class Mesh;
class GameObject;
class MeshFilter:public GeometryFilter
{
public:
	MeshFilter();
	~MeshFilter();
	void Awake(GameObject * pOwner);
	void SetSharedMesh(Mesh * pMesh);
	void Load(const char * path)
	{

	}
	size_t type_id()
	{
		return typeid(MeshFilter).hash_code();
	}
};

