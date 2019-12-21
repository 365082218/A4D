#include "stdafx.h"
#include "MeshGenerator.h"


MeshGenerator::MeshGenerator()
{
}


MeshGenerator::~MeshGenerator()
{
}

void MeshGenerator::CreateSphere(float radius)
{

}
void MeshGenerator::CreateCapsule()
{

}

void MeshGenerator::CreateCylinder(Mesh ** ppMesh, float radiusTop, float radiusBottom, float height)
{

}

void MeshGenerator::CreateBox(Mesh ** ppMesh, float width, float height, float depth)
{
	Mesh * pMesh = new Mesh();
	pMesh->vertexCount = 8;
	pMesh->subMeshCount = 1;
	pMesh->triangleCount = 12;

	pMesh->vec.push_back(D3DXVECTOR3(-width / 2.0f, -height / 2.0f, -depth / 2.0f));//D
	pMesh->vec.push_back(D3DXVECTOR3(-width / 2.0f, height / 2.0f, -depth / 2.0f));//A
	pMesh->vec.push_back(D3DXVECTOR3(width / 2.0f, height / 2.0f, -depth / 2.0f));//B
	pMesh->vec.push_back(D3DXVECTOR3(width / 2.0f, -height / 2.0f, -depth / 2.0f));//C
	pMesh->vec.push_back(D3DXVECTOR3(width / 2.0f, -height / 2.0f, depth / 2.0f));//G
	pMesh->vec.push_back(D3DXVECTOR3(width / 2.0f, height / 2.0f, depth / 2.0f));//F
	pMesh->vec.push_back(D3DXVECTOR3(-width / 2.0f, height / 2.0f, depth / 2.0f));//E
	pMesh->vec.push_back(D3DXVECTOR3(-width / 2.0f, -height / 2.0f, depth / 2.0f));//H

	A4D::getInstance()->Graphics()->pEditorDevice->CreateVertexBuffer(
		8 * sizeof(D3DXVECTOR3),
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ,
		D3DPOOL_MANAGED,
		&pMesh->VB,
		0);

	D3DXVECTOR3* vertices;
	pMesh->VB->Lock(0, 0, (void**)&vertices, 0);
	for (int i = 0; i < 8; i++)
		vertices[i] = pMesh->vec[i];
	pMesh->VB->Unlock();

	pMesh->IB = new IDirect3DIndexBuffer9*[1];
	for (int i = 0; i < 1; i++)
	{
		A4D::getInstance()->Graphics()->pEditorDevice->CreateIndexBuffer(
			36 * sizeof(WORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&pMesh->IB[i],
			0);
		WORD* indices = 0;
		pMesh->IB[i]->Lock(0, 0, (void**)&indices, 0);

		// front side
		indices[0] = 0; indices[1] = 1; indices[2] = 2;
		indices[3] = 0; indices[4] = 2; indices[5] = 3;

		// back side
		indices[6] = 4; indices[7] = 5; indices[8] = 6;
		indices[9] = 4; indices[10] = 6; indices[11] = 7;

		// right side
		indices[12] = 4; indices[13] = 2; indices[14] = 5;
		indices[15] = 4; indices[16] = 3; indices[17] = 2;

		// left side
		indices[18] = 6; indices[19] = 1; indices[20] = 0;
		indices[21] = 6; indices[22] = 0; indices[23] = 7;

		// top
		indices[24] = 1; indices[25] = 6; indices[26] = 2;
		indices[27] = 6; indices[28] = 5; indices[29] = 2;

		// bottom
		indices[30] = 3; indices[31] = 4; indices[32] = 7;
		indices[33] = 3; indices[34] = 7; indices[35] = 0;

		pMesh->IB[i]->Unlock();
	}
	if (ppMesh != NULL)
		*ppMesh = pMesh;
}

void MeshGenerator::CreatePlane(Mesh ** ppMesh, float width, float height)
{

}