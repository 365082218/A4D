#pragma once
#include "BaseMesh.h"
class Mesh;
class SubMesh:public BaseMesh
{
public:
	SubMesh(Mesh * mesh);
	~SubMesh();
	int _subIndexBufferStart;
	int _subIndexBufferCount;
	int _indexInMesh;
	IDirect3DVertexBuffer9 * _vertexBuffer;
	int _vertexStart = 0;
	/**@private */
	int _vertexCount = 0;
	/**@private */
	IDirect3DIndexBuffer9 * _indexBuffer;
	/**@private */
	int _indexStart;
	/**@private */
	int _indexCount;
	/**@private */
	vector<int> _indices;
	Mesh * _mesh;
	void _render(RenderState * rs);
};

