#pragma once
#include <iostream>  
#include <vector>
#include <map>
#include <list>
#include "Mesh.h"
#include "SubMesh.h"

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

