#pragma once
#include "Component.h"
class MeshFilter;
class RenderState;
class BoundBox;
class BoundSphere;
class RenderElement;
class Render :
	public Component
{
public:
	Render();
	~Render();
	void Awake(GameObject * pOwner);
	virtual void _render(RenderState * rs) = 0;
	void _renderUpdate(D3DXMATRIX * pMatrix);
	float sortingFudge;//≈≈–ÚΩ√’˝÷µ.
	float _distanceForSort;//≈≈–Ú÷µ.
	BoundBox * _boundingBox;
	BoundSphere * boundingSphere;
	void OnMeshChanged(AEvent * context);
	vector<RenderElement*> _renderElements;
	int _indexInSceneFrustumCullingObjects;
	void OnEnable(AEvent * context);
	void OnDisable(AEvent * context);
	MeshFilter * meshFilter;
	virtual void _changeRenderObjectsByMesh();
	virtual void _changeRenderObjectByMesh(int index);

};

