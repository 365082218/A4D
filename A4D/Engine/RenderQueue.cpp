#include "stdafx.h"
#include "RenderQueue.h"
#include "RenderElement.h"
#include "RenderState.h"
#include "Component.h"
#include "WGraphics.h"
#include "RenderTexture.h"
#include "BoundFrustum.h"
#include "Camera.h"
#include "resources.h"
#include "Vector3.h"
#include "BoundBox.h"
#include "BoundSphere.h"
#include "BaseMesh.h"
#include "GameObject.h"
#include "Render.h"
int RenderQueue::_uniqueIDCounter = 0;
RenderQueue::RenderQueue()
{
	_id = ++ _uniqueIDCounter;
}


RenderQueue::~RenderQueue()
{
}

void RenderQueue::_clearRenderElements()
{
	_dynamicBatchCombineRenderElements.clear();
	_renderElements.clear();
	_needSort = true;
}

void RenderQueue::_preRender(RenderState * rs)
{
	_finalElements.clear();
	if (_renderElements.size() != 0)
	{
		vector<RenderElement*>::iterator it = _renderElements.begin();
		while (it != _renderElements.end())
		{
			_finalElements.push_back(*it);
			it++;
		}
	}
	if (_dynamicBatchCombineRenderElements.size() != 0)
	{
		vector<RenderElement*>::iterator it = _dynamicBatchCombineRenderElements.begin();
		while (it != _dynamicBatchCombineRenderElements.end())
		{
			_finalElements.push_back(*it);
			it++;
		}
	}
}

void RenderQueue::_addRenderElement(RenderElement * renderElement)
{
	_renderElements.push_back(renderElement);
	_needSort = true;
}

//所有要渲染的对象都提交到渲染队列里
void RenderQueue::_render(RenderState * rs, bool yes)
{
	//int loopCount = Stat.loopCount;
	//Scene * scene = _scene;
	Camera * camera = rs->camera;
	rs->pDevice->SetTransform(D3DTS_VIEW, rs->_viewMatrix);
	rs->pDevice->SetTransform(D3DTS_PROJECTION, rs->_projectionMatrix);
	int cameraID = camera->id;
	IDirect3DVertexBuffer9** vbs;
	IDirect3DIndexBuffer9** IB;
	IDirect3DVertexBuffer9 * vertexBuffer;
	int vertexDeclaration;//fvf灵活顶点格式
	//shader;
	//var forceUploadParams = false;//提交参数.
	//var lastStateMaterial, lastStateOwner;
	for (int i = 0, n = _finalElements.size(); i < n; i++) {
		RenderElement * renderElement = _finalElements[i];
		BaseMesh * renderObj = renderElement->renderObj;
		rs->owner = renderElement->render->gameObject;
		if (renderObj != NULL)
			renderObj->_render(rs);
	}
}