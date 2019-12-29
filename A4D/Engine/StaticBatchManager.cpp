#include "stdafx.h"
#include "StaticBatchManager.h"
#include "EventDispatcher.h"
#include "Component.h"
#include "Node.h"
#include "Transform.h"
#include "GameObject.h"
#include "Layer.h"
#include "Scene.h"
#include "StaticBatch.h"

vector<StaticBatchManager*> * StaticBatchManager::_staticBatchManagers = NULL;
StaticBatchManager::StaticBatchManager()
{
}


StaticBatchManager::~StaticBatchManager()
{
}

void StaticBatchManager::_clearRenderElements()
{
	map<string, StaticBatch*>::iterator it;
	for (it = this->_staticBatches.begin(); it != this->_staticBatches.end(); it++)
		it->second->_clearRenderElements();
}


void StaticBatchManager::_addToRenderQueue(Scene * scene, D3DXMATRIX * view, D3DXMATRIX * projection, D3DXMATRIX * projectionView)
{
	map<string, StaticBatch*>::iterator it = _staticBatches.begin();
	for (it = _staticBatches.begin(); it != _staticBatches.end(); it++) {
		StaticBatch * staticBatch = it->second;
		if (staticBatch->_batchRenderElements.size() > 0)
			staticBatch->_updateToRenderQueue(scene, projectionView);
	}
}