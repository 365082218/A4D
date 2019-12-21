#include "stdafx.h"
#include "../A4D.h"
#include "W4DCommon.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include "global.h"
#include "Mesh.h"
#include <D3D10.h>
#include "SubMesh.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
TextureMesh::TextureMesh()
{
	A4D::getInstance()->Graphics()->pEditorDevice->CreateVertexBuffer(
		4 * sizeof(Tex_Vertex),
		D3DUSAGE_WRITEONLY,
		Tex_Vertex::TEX_FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);
	A4D::getInstance()->Graphics()->pEditorDevice->CreateIndexBuffer(
		3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);
	Tex_Vertex* vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);
	// vertices of a unit quad
	vertices[0] = Tex_Vertex(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f);//左上角
	vertices[1] = Tex_Vertex(1.0f, 1.0f, 0.0f, 1.0f, 0.0f);//右上角
	vertices[2] = Tex_Vertex(-1.0f, -1.0f, 0.0f, 0.0f, 1.0f);//左下角
	vertices[3] = Tex_Vertex(1.0f, -1.0f, 0.0f, 1.0f, 1.0f);//右下角
	VB->Unlock();

	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);
	// front side
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	//indices[3] = 1; indices[4] = 3; indices[5] = 2;
	IB->Unlock();
	// position and aim the camera
	position = D3DXVECTOR3(0.0f, 0.0f, -5.0f);
	target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// set projection matrix

	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI * 0.5f, // 90 - degree
		(float)800 / (float)600,
		1.0f,
		1000.0f);

	// set the render states
	D3DXMatrixIdentity(&world);
	string s = string("f:/github/Project/ptexture/nm001b01.tga");
	pTexture = NULL;
	HRESULT hr = D3DXCreateTextureFromFileA(A4D::getInstance()->Graphics()->pEditorDevice, s.c_str(), &pTexture);
}

void TextureMesh::Render(IDirect3DDevice9 * pDevice)
{
	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);

	//if (pTexture == null)
	//{
	//	HRESULT hr = D3DXCreateTextureFromFileA(pDevice, "f:/github/Project/ptexture/nm002b01.jpg", &pTexture);
	//	OutputDebugStringA("OK");
	//}
	pDevice->SetTransform(D3DTS_VIEW, &V);
	pDevice->SetTransform(D3DTS_PROJECTION, &proj);
	pDevice->SetTransform(D3DTS_WORLD, &world);
	pDevice->SetStreamSource(0, VB, 0, sizeof(Tex_Vertex));
	pDevice->SetTexture(0, pTexture);
	pDevice->SetIndices(IB);
	pDevice->SetFVF(Tex_Vertex::TEX_FVF);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 1);
}

PrimitiveMesh::PrimitiveMesh()
{

}

PrimitiveMesh::~PrimitiveMesh()
{

}

void PrimitiveMesh::_render(RenderState * rs)
{
	rs->pDevice->SetTransform(D3DTS_WORLD, rs->owner->transform->worldMatrix());
	rs->pDevice->SetStreamSource(0, this->VB, 0, sizeof(Vertex));
	int min = subMeshCount;
	rs->pDevice->SetFVF(Vertex::FVF);
	rs->pDevice->SetIndices(IB);
	rs->pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _numberVertices, 0, _numberIndices / 3);
}

QuadMesh::QuadMesh(float qlong, float qw)
{
	quadlong = qlong;
	quadwidth = qw;
	activeResource();
	getPositions();
	generateBoundingObject();
}

void QuadMesh::recreateResource()
{
	_numberVertices = 4;
	_numberIndices = 6;
	subMeshCount = 1;
	A4D::getInstance()->Graphics()->pEditorDevice->CreateVertexBuffer(
		_numberVertices * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);
	Vertex * pV = NULL;
	VB->Lock(0, _numberVertices * sizeof(Vertex), (void **)&pV, NULL);
	float halfLong = quadlong / 2;
	float halfWidth = quadwidth / 2;
	pV[0]._x = -halfLong;
	pV[0]._y = halfWidth;
	pV[0]._z = 0;

	pV[1]._x = halfLong;
	pV[1]._y = halfWidth;
	pV[1]._z = 0;

	pV[2]._x = -halfLong;
	pV[2]._y = -halfWidth;
	pV[2]._z = 0;

	pV[3]._x = halfLong;
	pV[3]._y = -halfWidth;
	pV[3]._z = 0;

	VB->Unlock();
	A4D::getInstance()->Graphics()->pEditorDevice->CreateIndexBuffer(
		_numberIndices * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);
	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;
	indices[4] = 2;
	indices[5] = 1;
	
	IB->Unlock();
	completeCreate();
}

PlaneMesh::PlaneMesh(float l, float w, int st, int sl)
{
	planelong = l;
	planewidth = w;
	stacks = st;
	slices = sl;
	activeResource();
	getPositions();
	generateBoundingObject();
}

void PlaneMesh::recreateResource()
{
	_numberVertices = (this->stacks + 1) * (this->slices + 1);
	_numberIndices = this->stacks * this->slices * 2 * 3;
	A4D::getInstance()->Graphics()->pEditorDevice->CreateVertexBuffer(
		_numberVertices * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);
	float * pV = NULL;
	VB->Lock(0, _numberVertices * sizeof(Vertex), (void **)&pV, NULL);
	float halfLong = planelong / 2;
	float halfWidth = planewidth / 2;
	float stacksLong = planelong / stacks;
	float slicksWidth = planewidth / slices;
	int verticeCount = 0;
	for (int i = 0; i < slices; i++)
	{
		for (int j = 0; j < stacks; j++)
		{
			pV[verticeCount++] = j * stacksLong - halfLong;
			pV[verticeCount++] = 0;
			pV[verticeCount++] = i * slicksWidth - halfWidth;
		}
	}
	VB->Unlock();

	A4D::getInstance()->Graphics()->pEditorDevice->CreateIndexBuffer(
		_numberIndices * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);
	WORD* indices = 0;
	int indiceIndex = 0;
	IB->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < this->slices; i++)
	{
		for (int j = 0; j < this->stacks; j++)
		{
			indices[indiceIndex++] = (i + 1)*(this->stacks + 1) + j;
			indices[indiceIndex++] = i * (this->stacks + 1) + j;
			indices[indiceIndex++] = (i + 1) * (this->stacks + 1) + j + 1;
			indices[indiceIndex++] = i * (this->stacks + 1) + j;
			indices[indiceIndex++] = i * (this->stacks + 1) + j + 1;
			indices[indiceIndex++] = (i + 1) * (this->stacks + 1) + j + 1;
		}
	}
	IB->Unlock();
	completeCreate();
}

SphereMesh::SphereMesh(float r, int st, int sl)
{
	stacks = st;
	slices = sl;
	radius = r;
	activeResource();
	getPositions();
	generateBoundingObject();
}

void SphereMesh::recreateResource()
{
	_numberVertices = (this->stacks + 1) * (this->slices + 1);
	_numberIndices = (3 * this->stacks * (this->slices + 1)) * 2;
	A4D::getInstance()->Graphics()->pEditorDevice->CreateVertexBuffer(
		_numberVertices * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);
	float * pV = NULL;
	VB->Lock(0, _numberVertices * sizeof(Vertex), (void **)&pV, NULL);
	float stackAngle = M_PI / stacks;
	float sliceAngle = M_PI * 2.0 / slices;
	int vertexIndex = 0;
	int verticeCount = 0;
	int indexCount = 0;
	WORD * indices2 = new WORD[_numberIndices];
	for (int stack = 0; stack < stacks + 1; stack++)
	{
		float r = sin(stack * stackAngle);
		float y = cos(stack * stackAngle);
		for (int slice = 0; slice < slices + 1; slice++)
		{
			float x = r * sin(slice * sliceAngle + M_PI * 1 / 2.0f);
			float z = r * cos(slice * sliceAngle + M_PI * 1 / 2.0f);
			pV[verticeCount+0] = x * radius;
			pV[verticeCount+1] = y * radius;
			pV[verticeCount+2] = z * radius;
			verticeCount += sizeof(Vertex) / 4;
			if (stack != stacks - 1)
			{
				indices2[indexCount++] = vertexIndex + slices + 1;
				indices2[indexCount++] = vertexIndex;
				indices2[indexCount++] = vertexIndex + 1;
				indices2[indexCount++] = vertexIndex + slices;
				indices2[indexCount++] = vertexIndex;
				indices2[indexCount++] = vertexIndex + slices + 1;
				vertexIndex++;
			}
		}
	}
	VB->Unlock();

	A4D::getInstance()->Graphics()->pEditorDevice->CreateIndexBuffer(
		_numberIndices * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);
	WORD* indices = 0;
	int indiceIndex = 0;
	IB->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < _numberIndices; i++)
	{
		indices[i] = indices2[i];
	}
	IB->Unlock();
	completeCreate();
}

BoxMesh::BoxMesh(float l, float w, float h)
{
	boxlong = l;//z轴
	boxwidth = w;//x轴
	boxheight = h;//y轴
	activeResource();
	getPositions();
	generateBoundingObject();
}

void BoxMesh::getPositions()
{
	//this->position;
}

void BoxMesh::recreateResource()
{
	_numberVertices = 24;
	_numberIndices = 36;
	subMeshCount = 1;

	//无材质色
	A4D::getInstance()->Graphics()->pEditorDevice->CreateVertexBuffer(
		_numberVertices * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);
	Vertex * pV = NULL;
	VB->Lock(0, _numberVertices * sizeof(Vertex), (void **)&pV, NULL);
	float halfLong = boxlong / 2;
	float halfHeight = boxheight / 2;
	float halfWidth = boxwidth / 2;
	pV[0]._x = -halfLong;
	pV[0]._y = halfHeight;
	pV[0]._z = -halfWidth;

	pV[1]._x = halfLong;
	pV[1]._y = halfHeight;
	pV[1]._z = -halfWidth;

	pV[2]._x = halfLong;
	pV[2]._y = halfHeight;
	pV[2]._z = halfWidth;

	pV[3]._x = halfLong;
	pV[3]._y = halfHeight;
	pV[3]._z = halfWidth;

	pV[4]._x = -halfLong;
	pV[4]._y = -halfHeight;
	pV[4]._z = -halfWidth;

	pV[5]._x = halfLong;
	pV[5]._y = -halfHeight;
	pV[5]._z = -halfWidth;

	pV[6]._x = halfLong;
	pV[6]._y = -halfHeight;
	pV[6]._z = halfWidth;

	pV[7]._x = -halfLong;
	pV[7]._y = -halfHeight;
	pV[7]._z = halfWidth;

	pV[8]._x = -halfLong;
	pV[8]._y = halfHeight;
	pV[8]._z = -halfWidth;

	pV[9]._x = -halfLong;
	pV[9]._y = halfHeight;
	pV[9]._z = halfWidth;

	pV[10]._x = -halfLong;
	pV[10]._y = -halfHeight;
	pV[10]._z = halfWidth;

	pV[11]._x = -halfLong;
	pV[11]._y = -halfHeight;
	pV[11]._z = -halfWidth;

	pV[12]._x = halfLong;
	pV[12]._y = halfHeight;
	pV[12]._z = -halfWidth;

	pV[13]._x = halfLong;
	pV[13]._y = halfHeight;
	pV[13]._z = halfWidth;

	pV[14]._x = halfLong;
	pV[14]._y = -halfHeight;
	pV[14]._z = halfWidth;

	pV[15]._x = halfLong;
	pV[15]._y = -halfHeight;
	pV[15]._z = -halfWidth;

	pV[16]._x = -halfLong;
	pV[16]._y = halfHeight;
	pV[16]._z = halfWidth;

	pV[17]._x = halfLong;
	pV[17]._y = halfHeight;
	pV[17]._z = halfWidth;

	pV[18]._x = halfLong;
	pV[18]._y = -halfHeight;
	pV[18]._z = halfWidth;

	pV[19]._x = -halfLong;
	pV[19]._y = -halfHeight;
	pV[19]._z = halfWidth;

	pV[20]._x = -halfLong;
	pV[20]._y = halfHeight;
	pV[20]._z = -halfWidth;

	pV[21]._x = halfLong;
	pV[21]._y = halfHeight;
	pV[21]._z = -halfWidth;

	pV[22]._x = halfLong;
	pV[22]._y = -halfHeight;
	pV[22]._z = -halfWidth;

	pV[23]._x = -halfLong;
	pV[23]._y = -halfHeight;
	pV[23]._z = -halfWidth;
	VB->Unlock();
	A4D::getInstance()->Graphics()->pEditorDevice->CreateIndexBuffer(
		_numberIndices * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&IB,
		0);
	WORD* indices = 0;
	IB->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
	indices[6] = 4;
	indices[7] = 7;
	indices[8] = 6;
	indices[9] = 6;
	indices[10] = 5;
	indices[11] = 4;
	indices[12] = 8;
	indices[13] = 9;
	indices[14] = 10;
	indices[15] = 10;
	indices[16] = 11;
	indices[17] = 8;
	indices[18] = 12;
	indices[19] = 15;
	indices[20] = 14;
	indices[21] = 14;
	indices[22] = 13;
	indices[23] = 12;
	indices[24] = 16;
	indices[25] = 17;
	indices[26] = 18;
	indices[27] = 18;
	indices[28] = 19;
	indices[29] = 16;
	indices[30] = 20;
	indices[31] = 23;
	indices[32] = 22;
	indices[33] = 22;
	indices[34] = 21;
	indices[35] = 20;
	IB->Unlock();
	completeCreate();
}



Mesh::Mesh()
{
	loaded = false;
	vertexCount = 0;//顶点数量
	subMeshCount = 0;//子网格数量
	//position = NULL;//顶点缓冲
	//indexCount = NULL;//索引缓冲
	triangleCount = 0;//三角面个数，每个三角面包含属于哪个子网格，以及3个顶点序号
}


Mesh::~Mesh()
{

}

void Mesh::_render(RenderState * rs)
{
	OutputDebugString(_T("渲染网格"));
}

IDirect3DIndexBuffer9  * Mesh::_getIndexBuffer()
{
	return NULL;
}

BaseMesh * Mesh::getRenderElement(int index)
{
	return this;
}

int Mesh::getRenderElementsCount()
{
	return subMeshCount;
}