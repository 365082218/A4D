#include "stdafx.h"
#include "SkcMeshFilter.h"
#include "SkcMesh.h"
#include "object.h"
REGISTER_CLASS(SkcMeshFilter)
SkcMeshFilter::SkcMeshFilter()
{
	this->_mesh = new SkcMesh();
}


SkcMeshFilter::~SkcMeshFilter()
{
}

void SkcMeshFilter::Load(const char * szFile)
{
	((SkcMesh*)this->_mesh)->LoadSkc(szFile);
	//((SkcMesh*)this->_mesh)->LoadSkcEx(szFile);
	if (this->_mesh->loaded)
		this->onevent(EventId::MeshChanged, NULL);
}