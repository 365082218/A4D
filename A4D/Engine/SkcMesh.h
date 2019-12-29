#pragma once
#include "Mesh.h"
class SkcMesh:public Mesh
{
public:
	SkcMesh();
	~SkcMesh();
	IDirect3DIndexBuffer9* IBEX;
	void LoadSkc(const char * szFile);
	BaseMesh * getRenderElement(int index);
	int getRenderElementsCount();
	void _render(RenderState * rs);
};

