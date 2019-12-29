#include "stdafx.h"
#include "Render.h"
#include "MeshRender.h"
#include "BaseMesh.h"
#include "Mesh.h"
#include "RenderState.h"
#include "RenderElement.h"
REGISTER_CLASS(MeshRender)
MeshRender::MeshRender()
{
}


MeshRender::~MeshRender()
{
}

void MeshRender::_render(RenderState * rs)
{

}

size_t MeshRender::type_id()
{
	return typeid(MeshRender).hash_code();
}