#include "stdafx.h"
#include "GeometryFilter.h"
#include "MeshFilter.h"
#include "Mesh.h"
#include "BaseMesh.h"
#include "Component.h"
#include "EventDispatcher.h"
#include "GameObject.h"
#include "Mesh.h"

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
	this->fire(EventId::MeshChanged, NULL);
}
