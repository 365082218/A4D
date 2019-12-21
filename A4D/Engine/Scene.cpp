#include "stdafx.h"
#include "RenderState.h"
#include "Camera.h"
#include "Scene.h"
#include "FrustumCulling.h"
#include "SceneManager.h"

Scene::Scene(string name)
{
	m_strName = name;
	state = new RenderState();
	m_pParent = NULL;
	_cullingRendersLength = 0;
	SceneManager::SetActiveScene(this);
}

Scene::~Scene()
{
}

void Scene::setParent(Node * parent)
{
	m_pParent = NULL;
}

void Scene::updateScene()
{
	for (int i = 0, n = m_pChild->size(); i < n; i++)
	{
		Node * p = m_pChild->at(i);
		Transform * trans = dynamic_cast<Transform*>(p);
		if (trans != NULL)
			trans->gameObject->update();
	}
}

//_prepareSceneToRender 场景更新前，灯光和相机啥的先准备好
void Scene::render()
{
	//遍历摄像机，
	for (int i = 0; i < this->cameraPool.size(); i++)
	{
		this->cameraPool[i]->_renderCamera(A4D::getInstance()->Graphics()->pEditorDevice, this->state, this);
	}
	
}


void Scene::OnPreRender()
{
	for (int i = 0, n = m_pChild->size(); i < n; i++)
	{
		Node * p = m_pChild->at(i);
		Transform * trans = dynamic_cast<Transform*>(p);
		if (trans != NULL)
			trans->gameObject->OnPreRender();
	}
}

void Scene::OnPostRender()
{
	for (int i = 0, n = m_pChild->size(); i < n; i++)
	{
		Node * p = m_pChild->at(i);
		Transform * trans = static_cast<Transform*>(p);
		if (trans != NULL)
			trans->gameObject->OnPostRender();
	}
	renderPool.clear();
}

//当该场景准备渲染前，准备所有要渲染的对象
void Scene::registerCamera(Camera * pCamera)
{
	if (pCamera == NULL)
		return;
	vector<Camera*>::iterator it = std::find(cameraPool.begin(), cameraPool.end(), pCamera);
	if (it == cameraPool.end())
		cameraPool.push_back(pCamera);
}

void Scene::unregisterCamera(Camera * pCamera)
{
	std::vector<Camera*>::iterator it = std::find(cameraPool.begin(), cameraPool.end(), pCamera);
	if (it != cameraPool.end())
		cameraPool.erase(it);
}

void Scene::registerRender(Render * pRender)
{
	std::vector<Render*>::iterator it = std::find(renderPool.begin(), renderPool.end(), pRender);
	renderPool.push_back(pRender);
}

/**
*初始化八叉树。
*@param width 八叉树宽度。
*@param height 八叉树高度。
*@param depth 八叉树深度。
*@param center 八叉树中心点
*@param level 八叉树层级。
*/
void Scene::initOctree(int width, int height, int depth, int center, int level) {
	//if (level == 0)
	//	level = 6;
	//this.treeSize = new D3DXVECTOR3(width, height, depth);
	//this.treeLevel = level;
	//this.treeRoot = new OctreeNode(this, 0);
	//this.treeRoot.init(center, this.treeSize);
}

void Scene::_preRenderScene(IDirect3DDevice9 * pDevice, RenderState * rs, BoundFrustum * pFrustum)
{
	D3DXMATRIX * view = &rs->_viewMatrix;
	D3DXMATRIX * projection = rs->_projectionMatrix;
	D3DXMATRIX * projectionView = rs->_projectionViewMatrix;
	int i = 0, iNum = 0;
	Camera * camera = rs->camera;
	if (camera->useOcclusionCulling) {
		//if (treeRoot)
		//	FrustumCulling.renderObjectCullingOctree(boundFrustum, this, camera, view, projection, projectionView);
		//else
		//	FrustumCulling.renderObjectCulling(boundFrustum, this, camera, view, projection, projectionView);
	}
	else
		FrustumCulling::renderObjectCullingNoBoundFrustum(this, camera, view, projection, projectionView);
	for (i = 0, iNum = this->_quenes.size(); i < iNum; i++)
	{
		if (_quenes[i] != NULL)
		{
			_quenes[i]->_preRender(state);
		}
	}
}

/**
*@inheritDoc
*/
void Scene::addFrustumCullingObject(Render * renderObject)
{
	//if (this.treeRoot) {
	//	this.addTreeNode(renderObject);
	//}
	//else {
		if (_cullingRendersLength == _cullingRenders.size())
			_cullingRenders.push_back(renderObject);
		else
			_cullingRenders[_cullingRendersLength] = renderObject;
		renderObject->_indexInSceneFrustumCullingObjects = _cullingRendersLength++;
	//}
}

/**
*@private
*/
void Scene::removeFrustumCullingObject(Render * renderObject)
{
	//if (treeRoot) {
	//	removeTreeNode(renderObject);
	//}
	//else {
	//	this._cullingRendersLength--;
	//	var indexInSceneFrustumCullingObjects = renderObject->_indexInSceneFrustumCullingObjects;
	//	if (indexInSceneFrustumCullingObjects != = this._cullingRendersLength) {
	//		var endRender = this._cullingRenders[this._cullingRendersLength];
	//		this._cullingRenders[indexInSceneFrustumCullingObjects] = endRender;
	//		endRender._indexInSceneFrustumCullingObjects = indexInSceneFrustumCullingObjects;
	//		renderObject._indexInSceneFrustumCullingObjects = -1;
	//	}
	//}
}

void Scene::_clear(IDirect3DDevice9 * pDevice, RenderState * rs)
{

}

void Scene::_renderScene(IDirect3DDevice9 * pDevice, RenderState * rs)
{
	Camera * camera = rs->camera;
	rs->pDevice = pDevice;
	rs->scene = this;
	int i = 0, n = 0;
	RenderQueue * queue;
	for (i = 0; i < 2; i++) {
		if (this->_quenes.size() > i)
		{
			queue = this->_quenes[i];
			if (queue) {
				camera->_renderTarget ? queue->_render(state, true) : queue->_render(state, false);
			}
		}
	}
	if (camera->clearFlag == /*laya.d3.core.BaseCamera.CLEARFLAG_SKY*/1) {
		//var sky = camera.sky;
		//if (sky) {
		//	WebGLContext.setCullFace(gl, false);
		//	WebGLContext.setDepthFunc(gl,/*laya.webgl.WebGLContext.LEQUAL*/0x0203);
		//	WebGLContext.setDepthMask(gl, false);
		//	sky._render(state);
		//	WebGLContext.setDepthFunc(gl,/*laya.webgl.WebGLContext.LESS*/0x0201);
		//	WebGLContext.setDepthMask(gl, true);
		//}
	}
	//for (i = 2, n = this._quenes.length; i < n; i++) {
	//	queue = this._quenes[i];
	//	if (queue) {
	//		queue._sortAlpha(state.camera.transform.position);
	//		camera.renderTarget ? queue._render(state, true) : queue._render(state, false);
	//	}
	//}
}

void Scene::_postRenderUpdateComponents(RenderState * rs)
{

}

RenderQueue * Scene::getRenderQueue(int index)
{
	int offset = index < 3000 ? 1 : 2;
	if (_quenes.size() == 0)
	{
		for (int i = 0; i < 3; i++)
			_quenes.push_back(NULL);
	}
	RenderQueue * p = _quenes.at(offset);
	if (p == NULL)
		_quenes[offset] = new RenderQueue(this);
	return _quenes.at(offset);
}