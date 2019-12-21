#pragma once
#include "Component.h"
#include "BoundSphere.h"
#include "BoundBox.h"
#include "MeshFilter.h"
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
	void OnMeshChanged(Event * context);
	vector<RenderElement*> _renderElements;
	int _indexInSceneFrustumCullingObjects;
	void OnEnable(Event * context);
	void OnDisable(Event * context);
	MeshFilter * meshFilter;
	virtual void _changeRenderObjectsByMesh();
	virtual void _changeRenderObjectByMesh(int index);

};

