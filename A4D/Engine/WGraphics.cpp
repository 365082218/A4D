#include "stdafx.h"
#include "WGraphics.h"
#include "SkcRender.h"
#include "RenderElement.h"
#include "Scene.h"
#include "SkcMeshFilter.h"
#include "Camera.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "../A4D.h"
#include "RenderState.h"
#include "RenderQueue.h"
#include "FrustumCulling.h"
#include "W4DCommon.h"
#include "Node.h"
#include "Component.h"
#include "Transform.h"
#include "GameObject.h"
#include "global.h"
#include "TexturePool.h"
#include "GameWorld.h"
#include "Console.h"
#include "WInputModel.h"
#include "MouseMgr.h"
#include "Pool.h"
#include "Time.h"
WGraphics::WGraphics()
{
	pGameDevice = NULL;
	state = new RenderState();
	_cullingRendersLength = 0;
}

void WGraphics::LoadSkc(char * file)
{
	GameObject * pHero = new GameObject("Unnamed");
	SkcRender * mr = (SkcRender*)pHero->addComponent(typeid(SkcRender).hash_code());
	SkcMeshFilter * mf = (SkcMeshFilter*)pHero->addComponent(typeid(SkcMeshFilter).hash_code());
	mf->Load(file);
	Transform * tri = (Transform*)mr->getComponent(typeid(Transform).hash_code());
	tri->SetPosition(0, 0, 0);
	tri->Scale(0.1f, 0.1f, 0.1f);
}
/*
建立编辑器模式下的场景和摄像机
*/
void WGraphics::Setup()
{
	pScene.push_back(new Scene("SampleScene"));
	for (int i = 0; i < 1; i++)
	{
		char buff[20];
		GameObject * pHero = new GameObject(string(itoa(i, buff, 10)));
		SkcRender * mr = (SkcRender*)pHero->addComponent(typeid(SkcRender).hash_code());
		SkcMeshFilter * mf = (SkcMeshFilter*)pHero->addComponent(typeid(SkcMeshFilter).hash_code());
		string s = string("F:/github/Project/pmodel/p") + string(itoa(i, buff, 10)) + string(".skc");
		mf->Load(s.c_str());
		Transform * tri = (Transform*)mr->getComponent(typeid(Transform).hash_code());
		//tri->SetPosition(-50 + (i % 5) * 20, -20, ((i / 5) + 1) * 35 + 100);
		//D3DXMatrixTranslation(&tri->localMatrix, 0, -20, 35);
		//tri->Scale(0.05f, 0.05f, 0.05f);
	}

	GameObject * pCamera = new GameObject();
	pEditCamera = dynamic_cast<Camera*>(pCamera->addComponent(typeid(Camera).hash_code()));
	Transform * cameraTrans = dynamic_cast<Transform*>(pEditCamera->getComponent(typeid(Transform).hash_code()));
	pCamera->addComponent("CameraMove");
	cameraTrans->SetPosition(0, 0, -100);

	//BOX
	//{
	//	GameObject * pBox = new GameObject();
	//	MeshRender * mr = (MeshRender*)pBox->addComponent(typeid(MeshRender).hash_code());
	//	MeshFilter * mf = (MeshFilter*)pBox->addComponent(typeid(MeshFilter).hash_code());
	//	mf->SetSharedMesh((Mesh*)new BoxMesh(20, 20, 20));
	//	Transform * tri = (Transform*)mr->getComponent(typeid(Transform).hash_code());
	//	tri->SetPosition(-50 + (0 % 5) * 20, -20, ((0 / 5) + 1) * 35 + 100);
	//	D3DXMatrixTranslation(&tri->localMatrix, 0, -20, 35);
	//}

	//QUAD
	//{
	//	GameObject * pBox = new GameObject();
	//	MeshRender * mr = (MeshRender*)pBox->addComponent(typeid(MeshRender).hash_code());
	//	MeshFilter * mf = (MeshFilter*)pBox->addComponent(typeid(MeshFilter).hash_code());
	//	mf->SetSharedMesh((Mesh*)new QuadMesh(20, 20));
	//	Transform * tri = (Transform*)mr->getComponent(typeid(Transform).hash_code());
	//	tri->SetPosition(-50 + (0 % 5) * 20, -20, 100);
	//	D3DXMatrixTranslation(&tri->localMatrix, 0, -20, 150);
	//}

	//Plane
	{
		//GameObject * pBox = new GameObject();
		//MeshRender * mr = (MeshRender*)pBox->addComponent(typeid(MeshRender).hash_code());
		//MeshFilter * mf = (MeshFilter*)pBox->addComponent(typeid(MeshFilter).hash_code());
		//mf->SetSharedMesh((Mesh*)new PlaneMesh(20.0, 20.0));
		//Transform * tri = (Transform*)mr->getComponent(typeid(Transform).hash_code());
		//tri->SetPosition(-50 + (0 % 5) * 20, -20, 100);
		//D3DXMatrixTranslation(&tri->localMatrix, 0, -20, 150);
	}

	//Sphere
	{
		GameObject * pBox = new GameObject();
		MeshRender * mr = (MeshRender*)pBox->addComponent(typeid(MeshRender).hash_code());
		MeshFilter * mf = (MeshFilter*)pBox->addComponent(typeid(MeshFilter).hash_code());
		mf->SetSharedMesh((Mesh*)new SphereMesh(10.0, 10, 10));
		Transform * tri = (Transform*)mr->getComponent(typeid(Transform).hash_code());
		tri->SetPosition(-50 + (0 % 5) * 20, -20, 250);
		D3DXMatrixTranslation(&tri->localMatrix, 0, -20, 250);
	}
	// set the render states
	
	pEditorDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);//线框
	//pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);//面
	pEditorDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);//不剪裁背面
	pEditorDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);//锯齿
	pEditorDevice->SetRenderState(D3DRS_LIGHTING, FALSE);//无光照-显示贴图(如果没有贴图则不显示) -如有光照则需自己处理材质，否则什么都看不见
}

WGraphics::~WGraphics()
{
}

bool WGraphics::Init(int _width, int _height, HWND hWnd, bool fullscreen)
{
	HRESULT hr = S_FALSE;
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
	d3dpp.BackBufferWidth = _width;
	d3dpp.BackBufferHeight = _height;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; //pixel format
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.Windowed = !fullscreen; // fullscreen
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // depth format
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pD3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3d9 != NULL)
	{
		hr = pD3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pEditorDevice);
		if (FAILED(hr))
		{
			::MessageBox(0, _T("CreateDevice() - FAILED"), 0, 0);
			return false;
		}
		hr = D3DXCreateSprite(pEditorDevice, &pSprite);
		if (FAILED(hr))
		{
			::MessageBox(0, _T("CreateSprite() - FAILED"), 0, 0);
			return false;
		}
	}
	width = _width;
	height = _height;
	return true;
}

void WGraphics::ReleaseGameDevice()
{
	//释放游戏运行状态的设备以及销毁游戏场景相关的.
}

void WGraphics::InitGameDevice()
{
	if (pGameDevice == NULL)
	{
		RECT rc;
		::GetWindowRect((HWND)A4D::getInstance()->winId(), &rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		HRESULT hr = S_FALSE;
		D3DPRESENT_PARAMETERS d3dpp;
		memset(&d3dpp, 0, sizeof(d3dpp));
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN; //pixel format
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = (HWND)A4D::getInstance()->winId();
		d3dpp.Windowed = true;
		d3dpp.EnableAutoDepthStencil = true;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8; // depth format
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		if (pD3d9 != NULL)
		{
			hr = pD3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, (HWND)A4D::getInstance()->winId(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pGameDevice);
			if (FAILED(hr))
			{
				::MessageBox(0, _T("CreateGameDevice() - FAILED"), 0, 0);
			}
		}
	}
}

void WGraphics::Loop()
{
	//运行场景刷新.
	HRESULT hr = S_FALSE;
	static float sc = 2.0f;
	//if (pGameDevice != null)
	//{
	//	frameCnt++;
	//	pGameDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//	pGameDevice->BeginScene();
	//	pGameDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	//	for (int i = 0; i < SceneManager::Instance()->sceneCount; i++)
	//	{
	//		Scene * pScene = SceneManager::Instance()->GetSceneAt(i);
	//		pScene->OnPreRender();
	//		pScene->updateScene();
	//		pScene->render();
	//		pScene->OnPostRender();
	//	}

	//	pGameDevice->EndScene();
	//	pGameDevice->Present(0, 0, 0, 0);
	//}
}

void WGraphics::UpdateGameObject()
{
	std::vector<Scene*>::iterator iter = pScene.begin();
	while (iter != pScene.end())
	{
		std::vector<GameObject*>::iterator iter2 = (*iter)->rootGameObjects.begin();
		while (iter2 != (*iter)->rootGameObjects.end())
		{
			(*iter2)->update();
			iter2++;
		}
		iter++;
	}
}

void WGraphics::EditorUpdate()
{
	//编辑器场景刷新.
	//画按钮，画场景，画各个面板
	//编辑器环境下，运行和游戏面板下基本一致
	HRESULT hr = S_FALSE;
	if (pEditorDevice != NULL)
	{
		pEditorDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0XFFFFFFFF, 1.0f, 0);
		pEditorDevice->BeginScene();
		UpdateGameObject();
		Draw();
		A4D::getInstance()->pWorld->Draw();
		pEditorDevice->EndScene();
		pEditorDevice->Present(0, 0, 0, 0);
	}
}

void WGraphics::Draw()
{
	//遍历摄像机，
	for (int i = 0; i < this->cameraPool.size(); i++)
	{
		this->cameraPool[i]->_renderCamera(A4D::getInstance()->Graphics()->pEditorDevice, this->state, this);
	}
}

//当该场景准备渲染前，准备所有要渲染的对象
void WGraphics::RegisterCamera(Camera * pCamera)
{
	if (pCamera == NULL)
		return;
	vector<Camera*>::iterator it = std::find(cameraPool.begin(), cameraPool.end(), pCamera);
	if (it == cameraPool.end())
		cameraPool.push_back(pCamera);
}

void WGraphics::UnregisterCamera(Camera * pCamera)
{
	std::vector<Camera*>::iterator it = std::find(cameraPool.begin(), cameraPool.end(), pCamera);
	if (it != cameraPool.end())
		cameraPool.erase(it);
}

void WGraphics::RegisterRender(Render * pRender)
{
	std::vector<Render*>::iterator it = std::find(renderPool.begin(), renderPool.end(), pRender);
	renderPool.push_back(pRender);
}


void WGraphics::ShutDown()
{
	if (pEditorDevice)
	{
		pEditorDevice->Release();
		pEditorDevice = 0;
	}
}

void WGraphics::_preRenderScene(IDirect3DDevice9 * pDevice, RenderState * rs, BoundFrustum * pFrustum)
{
	D3DXMATRIX * view = &rs->_viewMatrix;
	D3DXMATRIX * projection = &rs->_projectionMatrix;
	D3DXMATRIX * projectionView = &rs->_projectionViewMatrix;
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

void WGraphics::addFrustumCullingObject(Render * renderObject)
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

void WGraphics::removeFrustumCullingObject(Render * renderObject)
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

void WGraphics::_clear(IDirect3DDevice9 * pDevice, RenderState * rs)
{

}

void WGraphics::_renderScene(IDirect3DDevice9 * pDevice, RenderState * rs)
{
	Camera * camera = rs->camera;
	rs->pDevice = pDevice;
	//rs->scene = this;
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

void WGraphics::_postRenderUpdateComponents(RenderState * rs)
{

}

RenderQueue * WGraphics::getRenderQueue(int index)
{
	int offset = index < 3000 ? 1 : 2;
	if (_quenes.size() == 0)
	{
		for (int i = 0; i < 3; i++)
			_quenes.push_back(NULL);
	}
	RenderQueue * p = _quenes.at(offset);
	if (p == NULL)
		_quenes[offset] = new RenderQueue();
	return _quenes.at(offset);
}