#include "stdafx.h"
#include "SkcMeshFilter.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "resources.h"
#include "BaseMesh.h"
#include "Mesh.h"
#include "SkcMesh.h"
#include "GeometryFilter.h"
#include "MeshFilter.h"
#include "GameObject.h"
#include "Transform.h"
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
		this->fire(EventId::MeshChanged, NULL);
}