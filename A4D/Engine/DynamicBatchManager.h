#pragma once
#include "Material.h"
class Material;
class DynamicBatchManager
{
public:
	DynamicBatchManager();
	~DynamicBatchManager();
	void _clearRenderElements();
	vector<RenderElement*> _combineRenderElements;
	vector<Material*>_materials;
	vector<int> _materialToRenderElementsOffsets;
	vector<RenderElement*> _prepareDynamicBatchCombineElements;
	int _currentCombineVertexCount;
	int _currentCombineIndexCount;
	void _addPrepareRenderElement(RenderElement * element);
	void _addToRenderQueue(Scene * scene, D3DXMATRIX * view, D3DXMATRIX * projection, D3DXMATRIX * projectionView);
	void _finishCombineDynamicBatch(Scene * scene);
};

