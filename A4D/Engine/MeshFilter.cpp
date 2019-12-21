#include "stdafx.h"
#include "MeshFilter.h"
#include "object.h"
REGISTER_CLASS(MeshFilter)
MeshFilter::MeshFilter()
{
}


MeshFilter::~MeshFilter()
{
}

void MeshFilter::Awake(GameObject * pOwner)
{

}

void MeshFilter::SetSharedMesh(Mesh * pMesh)
{
	this->_mesh = pMesh;
	this->onevent(EventId::MeshChanged, NULL);
}
