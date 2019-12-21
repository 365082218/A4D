#pragma once
#include <iostream>  
#include <vector>
#include <map>
#include <list>
#include "BoneWeight.h"
#include "MaterialUnit.h"
#include "W4DCommon.h"
using namespace std;
#include <vector>
#include "SubMesh.h"
struct D3DXVECTOR3;
struct Vertex;
class PrimitiveMesh :public BaseMesh
{
public:
	PrimitiveMesh();
	~PrimitiveMesh();
	int _numberVertices;//��������
	int _numberIndices;//��������
	IDirect3DVertexBuffer9* VB;
	IDirect3DIndexBuffer9* IB;
	void _render(RenderState * rs);
	virtual int getRenderElementsCount() {
		return 1;
	}
	/**
	*��ȡ��Ⱦ��Ԫ,�����ش˷�����
	*@param index ������
	*@return ��Ⱦ��Ԫ��
	*/
	virtual BaseMesh * getRenderElement(int index) {
		return this;
	}
};

//class TestBoxMesh
//{
//public:
//	IDirect3DVertexBuffer9* VB;
//	IDirect3DIndexBuffer9* IB;
//	TestBoxMesh();
//
//	void Render(IDirect3DDevice9 * pDevice);
//
//	D3DXVECTOR3 position;
//	D3DXVECTOR3 target;
//	D3DXVECTOR3 up;
//	D3DXMATRIX proj;
//	D3DXMATRIX world;
//};

class TextureMesh :public PrimitiveMesh
{
public:
	TextureMesh();
	void Render(IDirect3DDevice9 * pDevice);
	void _render(RenderState * rs)
	{

	}
	D3DXVECTOR3 position;
	D3DXVECTOR3 target;
	D3DXVECTOR3 up;
	D3DXMATRIX proj;
	D3DXMATRIX world;
	LPDIRECT3DTEXTURE9 pTexture;
};

//2����Ƭ
class QuadMesh :public PrimitiveMesh
{
public:
	QuadMesh(float qlong, float qwidth);
	float quadlong;
	float quadwidth;
	void recreateResource();
};

//1��ƽ��
class PlaneMesh :public PrimitiveMesh
{
public:
	PlaneMesh(float plong, float pwidth, int st = 10, int sl = 10);
	float planelong;
	float planewidth;
	int stacks;//��ֶ�
	int slices;//���ֶ�
	void recreateResource();
};

//Բ������Բ׶��
class CylinderMesh :public PrimitiveMesh
{

};

//������
class CapsuleMesh :public PrimitiveMesh
{

};

//����
class SphereMesh :public PrimitiveMesh
{
public:
	SphereMesh(float r, int stacks = 5, int slices = 5);
	int stacks;
	int slices;
	float radius;
	void recreateResource();
};

class BoxMesh :public PrimitiveMesh
{
public:
	BoxMesh(float l = 1.0f, float w = 1.0f, float h = 1.0f);
	void recreateResource();
	float boxlong;
	float boxwidth;
	float boxheight;
	void getPositions();
};

class Mesh:public BaseMesh
{
public:
	Mesh();
	~Mesh();

	int vertexCount;//��������
	IDirect3DVertexBuffer9* VB;
	IDirect3DIndexBuffer9** IB;
	int triangleCount;//�����������ÿ����������������ĸ��������Լ�3���������.
	int _vertexBufferCount;//���㻺��������
	string Skin;
	int StaticSkins;
	MaterialUnit ** materials;
	vector<BoneWeight> boneWeight;
	vector<D3DVECTOR> vec;
	vector<D3DXVECTOR2> uv;
	map<int, vector<int>> indic;
	void _render(RenderState * rs);
	IDirect3DIndexBuffer9  * _getIndexBuffer();
	vector<SubMesh*> _subMeshes;
	virtual int getRenderElementsCount();
	virtual BaseMesh * getRenderElement(int index);
	bool loaded;
};

class GMBMesh :public BaseMesh
{
public:
	GMBMesh();
	~GMBMesh();
	int vertexCount;//��������
	IDirect3DVertexBuffer9* VB;
	IDirect3DIndexBuffer9** IB;
	int triangleCount;//�����������ÿ����������������ĸ��������Լ�3���������.
	int _vertexBufferCount;//���㻺��������
	string Skin;
	int StaticSkins;
	MaterialUnit ** materials;
	vector<BoneWeight> boneWeight;
	vector<D3DVECTOR> vec;
	vector<D3DXVECTOR2> uv;
	map<int, vector<int>> indic;
	void _render(RenderState * rs);
	IDirect3DIndexBuffer9  * _getIndexBuffer();
	vector<SubMesh*> _subMeshes;
	virtual int getRenderElementsCount();
	virtual BaseMesh * getRenderElement(int index);
	bool loaded;
};