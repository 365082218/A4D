#pragma once
#include "StaticBatch.h"
class StaticBatch;
class StaticBatchManager
{
public:
	StaticBatchManager();
	~StaticBatchManager();
	map<string, StaticBatch*> _staticBatches;
	static vector<StaticBatchManager*> * _staticBatchManagers;
	void _clearRenderElements();
	void _addToRenderQueue(Scene * scene, D3DXMATRIX * view, D3DXMATRIX * projection, D3DXMATRIX * projectionView);
};

