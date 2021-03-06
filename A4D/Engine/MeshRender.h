#pragma once
#include "Render.h"
class Mesh;
class RenderState;
class MeshRender:public Render
{
public:
	MeshRender();
	MeshRender(Mesh * mesh);
	~MeshRender();
	void _render(RenderState * rs);
public:
	Mesh * pMesh;
	size_t type_id();
};

