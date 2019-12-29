#include "stdafx.h"
#include "DynamicBatchManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "RenderElement.h"
#include "Material.h"
#include "StaticBatch.h"
#include "Render.h"
#include "BaseMesh.h"
#include "RenderState.h"
#include "BoundBox.h"
#include "BoundSphere.h"
#include "Camera.h"

DynamicBatchManager::DynamicBatchManager()
{
}


DynamicBatchManager::~DynamicBatchManager()
{
}

void DynamicBatchManager::_clearRenderElements()
{
	_combineRenderElements.clear();
	_materials.clear();
	_materialToRenderElementsOffsets.clear();
	_currentCombineVertexCount = 0;
	_currentCombineIndexCount = 0;
}

void DynamicBatchManager::_addPrepareRenderElement(RenderElement * element)
{
	_prepareDynamicBatchCombineElements.push_back(element);
}

void DynamicBatchManager::_addToRenderQueue(Scene * scene, D3DXMATRIX * view, D3DXMATRIX * projection, D3DXMATRIX * projectionView)
{

}

void DynamicBatchManager::_finishCombineDynamicBatch(Scene * scene)
{

}
