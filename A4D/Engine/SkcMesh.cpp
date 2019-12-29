#include "stdafx.h"
#include "EventDispatcher.h"
#include "resources.h"
#include "BaseMesh.h"
#include "Mesh.h"
#include "SkcMesh.h"
#include "RenderState.h"
#include "MaterialUnit.h"
#include "BoneWeight.h"
#include "../A4D.h"
#include "W4DCommon.h"
#include "Node.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "global.h"
#include "WGraphics.h"
#include "TexturePool.h"
#include "GameWorld.h"
#include "Console.h"
#include "WInputModel.h"
#include "MouseMgr.h"
#include "Pool.h"
#include "Time.h"
SkcMesh::SkcMesh()
{
}


SkcMesh::~SkcMesh()
{
}

void SkcMesh::LoadSkc(const char * szFile)
{
	fstream f(szFile);
	string line;
	int i = 0;
	int pos = i + 1;
	int left = 0;
	int matidx = -1;
	while (getline(f, line))
	{
		if (line.find_first_of('#') != -1)
			continue;
		if (line.length() == 0)
			continue;
		vector<string> lineobj = split(line, " ");
		if (lineobj[0] == "Static" && lineobj[1] == "Skins:")
		{
			StaticSkins = atoi(lineobj[2].c_str());
			pos = i + 1;
			left = 0;
			matidx = -1;
		}
		else if (lineobj[0] == "Static" && lineobj[1] == "Skin" && lineobj.size() == 3)
		{
			Skin = lineobj[2];
		}
		else if (lineobj[0] == "{")
		{
			left++;
		}
		else if (lineobj[0] == "}")
		{
			left--;
			if (left == 0)
				break;
		}
		else if (lineobj[0] == "Materials:")
		{
			subMeshCount = atoi(lineobj[1].c_str());
			materials = new MaterialUnit *[subMeshCount];
		}
		else if (lineobj[0] == "Material")
		{
			matidx++;
			materials[matidx] = new MaterialUnit();
		}
		else if (lineobj[0] == "Texture")
		{
			string text = lineobj[1];
			materials[matidx]->Texture = text;
		}
		else if (lineobj[0] == "ColorKey")
		{
			materials[matidx]->ColorKey = D3DCOLOR_COLORVALUE(atof(lineobj[1].c_str()), atof(lineobj[2].c_str()), atof(lineobj[3].c_str()), atof(lineobj[4].c_str()));
		}
		else if (lineobj[0] == "Ambient")
		{
			materials[matidx]->Ambient = D3DCOLOR_COLORVALUE(atof(lineobj[1].c_str()), atof(lineobj[2].c_str()), atof(lineobj[3].c_str()), 0);
		}
		else if (lineobj[0] == "Diffuse")
		{
			materials[matidx]->Diffuse = D3DCOLOR_COLORVALUE(atof(lineobj[1].c_str()), atof(lineobj[2].c_str()), atof(lineobj[3].c_str()), 0);
		}
		else if (lineobj[0] == "Specular")
		{
			materials[matidx]->ColorKey = D3DCOLOR_COLORVALUE(atof(lineobj[1].c_str()), atof(lineobj[2].c_str()), atof(lineobj[3].c_str()), 0);
		}
		else if (lineobj[0] == "Emissive")
		{
			materials[matidx]->ColorKey = D3DCOLOR_COLORVALUE(atof(lineobj[1].c_str()), atof(lineobj[2].c_str()), atof(lineobj[3].c_str()), 0);
		}
		else if (lineobj[0] == "Opacity")
		{
			materials[matidx]->Opacity = atof(lineobj[1].c_str());
		}
		else if (lineobj[0] == "Option")
		{
			materials[matidx]->Option = lineobj[1];
		}
		else if (lineobj[0] == "TwoSide")
		{
			materials[matidx]->TwoSide = (lineobj[1] == "TRUE");
		}
		else if (lineobj[0] == "Vertices:")
		{
			vertexCount = atoi(lineobj[1].c_str());
		}
		else if (lineobj[0] == "v")
		{
			D3DVECTOR v;
			v.x = atof(lineobj[1].c_str());
			v.z = atof(lineobj[2].c_str());
			v.y = atof(lineobj[3].c_str());

			D3DXVECTOR2 uvv;
			uvv.x = atof(lineobj[5].c_str());
			uvv.y = atof(lineobj[6].c_str());
			BoneWeight weight;
			int boneCtrlNum = atoi(lineobj[8].c_str());
			switch (boneCtrlNum)
			{
			case 1:
				weight.boneIndex0 = atoi(lineobj[9].c_str());
				weight.weight0 = atof(lineobj[10].c_str());
				break;
			case 2:
				weight.boneIndex0 = atoi(lineobj[9].c_str());
				weight.weight0 = atof(lineobj[10].c_str());
				weight.boneIndex1 = atoi(lineobj[11].c_str());
				weight.weight1 = atof(lineobj[12].c_str());
				break;
			case 3:
				weight.boneIndex0 = atoi(lineobj[9].c_str());
				weight.weight0 = atof(lineobj[10].c_str());
				weight.boneIndex1 = atoi(lineobj[11].c_str());
				weight.weight1 = atof(lineobj[12].c_str());
				weight.boneIndex2 = atoi(lineobj[13].c_str());
				weight.weight2 = atof(lineobj[14].c_str());
				break;
			case 4:
				weight.boneIndex0 = atoi(lineobj[9].c_str());
				weight.weight0 = atof(lineobj[10].c_str());
				weight.boneIndex1 = atoi(lineobj[11].c_str());
				weight.weight1 = atof(lineobj[12].c_str());
				weight.boneIndex2 = atoi(lineobj[13].c_str());
				weight.weight2 = atof(lineobj[14].c_str());
				weight.boneIndex3 = atoi(lineobj[15].c_str());
				weight.weight3 = atof(lineobj[16].c_str());
				break;
			}
			boneWeight.push_back(weight);
			vec.push_back(v);
			uv.push_back(uvv);
		}
		else if (lineobj[0] == "f")
		{
			int o = 0;
			int p = 0;
			int q = 0;
			int matIdx2 = 0;
			matIdx2 = atoi(lineobj[2].c_str());
			o = atoi(lineobj[3].c_str());
			p = atoi(lineobj[4].c_str());
			q = atoi(lineobj[5].c_str());
			vector<int> ind;
			ind.push_back(o);
			ind.push_back(q);
			ind.push_back(p);

			if (indic.find(matIdx2) != indic.end())
			{
				indic[matIdx2].push_back(o);
				indic[matIdx2].push_back(q);
				indic[matIdx2].push_back(p);
			}
			else
			{
				indic.insert(pair<int, vector<int>>(matIdx2, ind));
			}
		}
		else if (lineobj[0] == "Triangles:")
		{
			triangleCount = atoi(lineobj[1].c_str());
		}
		else
		{
		}
	}


	A4D::getInstance()->Graphics()->pEditorDevice->CreateVertexBuffer(
		vertexCount * sizeof(Tex_Vertex),
		D3DUSAGE_WRITEONLY,
		Tex_Vertex::TEX_FVF,
		D3DPOOL_MANAGED,
		&VB,
		0);

	Tex_Vertex * vertices;
	VB->Lock(0, 0, (void**)&vertices, 0);
	for (int i = 0; i < vertexCount; i++)
		vertices[i] = Tex_Vertex(vec[i].x, vec[i].y, vec[i].z, uv[i].x, 1 - uv[i].y);
	VB->Unlock();
	IB = new IDirect3DIndexBuffer9*[subMeshCount];
	for (int i = 0; i < subMeshCount; i++)
	{
		if (indic[i].size() == 0)
			continue;
		A4D::getInstance()->Graphics()->pEditorDevice->CreateIndexBuffer(
			indic[i].size() * sizeof(WORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&IB[i],
			0);
		WORD* indices = 0;
		IB[i]->Lock(0, 0, (void**)&indices, 0);

		int k = 0;
		vector<int>::iterator it = indic[i].begin();
		while (it != indic[i].end())
		{
			indices[k] = *it;
			it++;
			k++;
		}

		IB[i]->Unlock();
	}
	pTexture = new LPDIRECT3DTEXTURE9[subMeshCount];
	for (int i = 0; i < subMeshCount; i++)
	{
		if (indic[i].size() == 0)
			continue;

		string s = string("f:/github/Project/ptexture/") + materials[i]->Texture;
		HRESULT hr = D3DXCreateTextureFromFileA(A4D::getInstance()->Graphics()->pEditorDevice, s.c_str(), &pTexture[i]);
		if (FAILED(hr))
			MessageBoxA(0, s.c_str(), "msg", MB_OK);
	}

	this->loaded = true;
}

BaseMesh * SkcMesh::getRenderElement(int index)
{
	return this;
	//return this->_subMeshes[index];
}

int SkcMesh::getRenderElementsCount()
{
	return 1;
	//return this->subMeshCount;
}

void SkcMesh::_render(RenderState * rs)
{
	rs->pDevice->SetTransform(D3DTS_WORLD, rs->owner->transform->worldMatrix());
	rs->pDevice->SetStreamSource(0, this->VB, 0, sizeof(Tex_Vertex));
	int min = subMeshCount;
	//min = 2;
	for (int i = 0; i < min; i++)
	{
		rs->pDevice->SetTexture(0, this->pTexture[i]);
		rs->pDevice->SetFVF(Tex_Vertex::TEX_FVF);
		rs->pDevice->SetIndices(this->IB[i]);
		rs->pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, indic[i].size() / 3);
	}
	//rs->pDevice->SetFVF(Tex_Vertex::TEX_FVF);
	//rs->pDevice->SetIndices(this->IBEX);
	//rs->pDevice->SetTexture(0, this->pTexture[0]);
	//rs->pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
}