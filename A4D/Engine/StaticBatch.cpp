#include "stdafx.h"
#include "StaticBatch.h"


StaticBatch::StaticBatch()
{
}


StaticBatch::~StaticBatch()
{
}

void StaticBatch::_clearRenderElements()
{
	_batchRenderElements.clear();
}

void StaticBatch::_addBatchRenderElement(RenderElement* renderElement) {
	//在二分查找到的位置插入.
	//_batchRenderElements.splice(this._binarySearch(renderElement), 0, renderElement);
}

void StaticBatch::_updateToRenderQueue(Scene * scene, D3DXMATRIX * projectionView) {
	_combineRenderElementPoolIndex = 0;
	//_getRenderElement(scene->getRenderQueue(_material->renderQueue)->_renderElements, scene, projectionView);
}