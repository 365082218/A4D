#include "stdafx.h"
#include "Component.h"
#include "Render.h"
#include "MeshRender.h"
#include "object.h"

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