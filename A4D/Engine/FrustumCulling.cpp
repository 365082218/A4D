#include "stdafx.h"
#include "FrustumCulling.h"
#include "StaticBatchManager.h"
#include "StaticBatch.h"
#include "DynamicBatchManager.h"
#include "Camera.h"
#include "Transform.h"
#include "Layer.h"
#include "Component.h"
#include "Render.h"
#include "Vector3.h"
#include "RenderElement.h"
#include "BaseMaterial.h"
FrustumCulling::FrustumCulling()
{
}


FrustumCulling::~FrustumCulling()
{
}

void FrustumCulling::renderObjectCullingNoBoundFrustum(Scene * scene, Camera * camera, D3DXMATRIX * view, D3DXMATRIX * projection, D3DXMATRIX * projectionView)
{
	//得到摄像机视锥内的渲染对象，每个渲染对象的子对象按各自材质提交到渲染队列
	//int i = 0, n = 0, j = 0, m = 0;
	//vector<RenderQueue*> * queues = &scene->_quenes;
	DynamicBatchManager * dynamicBatchManager = scene->_dynamicBatchManager;
	vector<Render*> frustumCullingObjects = scene->_cullingRenders;
	for (int i = 0, n = scene->_quenes.size(); i < n; i++) {
		RenderQueue * queue = scene->_quenes[i];
		if (queue != NULL)
			queue->_clearRenderElements();
	};
	//vector<StaticBatchManager*> * staticBatchManagers = StaticBatchManager::_staticBatchManagers;
	//for (i = 0, n = StaticBatchManager::_staticBatchManagers->size(); i < n; i++)
	//	staticBatchManagers->at(i)->_clearRenderElements();
	//dynamicBatchManager->_clearRenderElements();
	D3DXVECTOR3 *cameraPosition = &(camera->gameObject->transform->position);
	for (int i = 0, n = scene->_cullingRendersLength; i < n; i++) {
		Render * baseRender = frustumCullingObjects[i];
		if (Layer::isVisible(baseRender->gameObject->layer.mask) && baseRender->enable) {
			baseRender->_renderUpdate(projectionView);
			baseRender->_distanceForSort = Vector3::distance(&baseRender->boundingSphere->center, cameraPosition) + baseRender->sortingFudge;
			vector<RenderElement*> * renderElements = &baseRender->_renderElements;
			for (int j = 0, m = renderElements->size(); j < m; j++) {
				RenderElement * renderElement = renderElements->at(j);
				StaticBatch * staticBatch = renderElement->_staticBatch;
				if (staticBatch && (staticBatch->_material == renderElement->_material)) {
					staticBatch->_addBatchRenderElement(renderElement);
				}
				else {
					BaseMesh * renderObj = renderElement->renderObj;
					//if ((renderObj->triangleCount < /*laya.d3.graphics.DynamicBatch.maxCombineTriangleCount*/10) && (renderObj->_vertexBufferCount == 1) && (renderObj->_getIndexBuffer()) && (renderElement->_material->renderQueue < 2) && renderElement->_canDynamicBatch && (!baseRender->m_pOwner->isStatic))
					//	dynamicBatchManager->_addPrepareRenderElement(renderElement);
					//else
						//scene->getRenderQueue(renderElement->_material->renderQueue)->_addRenderElement(renderElement);
						scene->getRenderQueue(2000)->_addRenderElement(renderElement);
				}
			}
		}
	}
	//for (int i = 0, n = staticBatchManagers->size(); i < n; i++)
	//	staticBatchManagers->at(i)->_addToRenderQueue(scene, view, projection, projectionView);
	//dynamicBatchManager->_finishCombineDynamicBatch(scene);
	//dynamicBatchManager->_addToRenderQueue(scene, view, projection, projectionView);
}
