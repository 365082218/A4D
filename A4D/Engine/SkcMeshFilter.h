#pragma once
#include "MeshFilter.h"
class SkcMeshFilter:public MeshFilter
{
public:
	SkcMeshFilter();
	~SkcMeshFilter();
	void Load(const char * path);
	size_t type_id()
	{
		return typeid(SkcMeshFilter).hash_code();
	}
};

