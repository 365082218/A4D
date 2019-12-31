#include "stdafx.h"
#include "RenderState.h"

RenderState::RenderState()
{
	D3DXMatrixIdentity((D3DXMATRIX*)&_viewMatrix);
	D3DXMatrixIdentity((D3DXMATRIX*)&_projectionMatrix);
	D3DXMatrixIdentity((D3DXMATRIX*)&_projectionViewMatrix);
}


RenderState::~RenderState()
{
}
