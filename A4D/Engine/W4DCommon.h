#pragma once
#include <D3DX10Math.h>
#include "Mesh.h"

struct Tex_Vertex
{
	Tex_Vertex() {}
	Tex_Vertex(float x, float y, float z, float u, float v)
	{
		_x = x; _y = y; _z = z;
		_u = u; _v = v;
	}
	float _x, _y, _z;
	float _u, _v;
	static const DWORD TEX_FVF = D3DFVF_XYZ | D3DFVF_TEX1;//skc网格，位置+uv
};

struct Vertex
{
	Vertex() {}
	Vertex(float x, float y, float z)
	{
		_x = x; _y = y; _z = z;
	}
	float _x, _y, _z;
	static const DWORD FVF = D3DFVF_XYZ;;
};

//地图 顶点+uv+颜色
struct GMBVertex
{
	GMBVertex() {}
	GMBVertex(float x, float y, float z, float u, float v, D3DCOLOR color)
	{
		_x = x; _y = y; _z = z;
		_u = u; _v = v;
		c = color;
	}
	float _x, _y, _z;
	float _u, _v;
	D3DCOLOR c;
	static const DWORD TEX_FVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_DIFFUSE;//skc网格，位置+uv
};