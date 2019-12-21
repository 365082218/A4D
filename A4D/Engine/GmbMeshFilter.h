#pragma once
#include "MeshFilter.h"
class GmbMeshFilter :
	public MeshFilter
{
public:
	GmbMeshFilter();
	~GmbMeshFilter();
	void loadDes(string des);
};
