#pragma once
class RenderElement;
class BaseMaterial;
class StaticBatch
{
public:
	StaticBatch();
	~StaticBatch();
	vector<RenderElement*> _batchRenderElements;
	void _clearRenderElements();
	void _addBatchRenderElement(RenderElement* renderElement);
	void _updateToRenderQueue(Scene * scene, D3DXMATRIX * projectionView);
	BaseMaterial * _material;
	int _combineRenderElementPoolIndex;
};

