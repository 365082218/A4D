#include "stdafx.h"
#include "Mesh.h"
#include "SkcRender.h"
#include "MeshRender.h"
#include "SceneManager.h"
#include "SkcMeshFilter.h"
#include "GameWorld.h"

using namespace std;
WGraphics::WGraphics()
{
	frameCnt = 0;
	pGameDevice = NULL;
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
	pEditScene = new Scene();
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

bool WGraphics::Init(int width, int height, HWND hWnd, bool fullscreen)
{
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
		pEditScene->OnPreRender();
		pEditScene->updateScene();
		pEditScene->render();
		pEditScene->OnPostRender();
		A4D::getInstance()->pWorld->Draw();
		pEditorDevice->EndScene();
		pEditorDevice->Present(0, 0, 0, 0);
	}
}

void WGraphics::ShutDown()
{
	if (pEditorDevice)
	{
		pEditorDevice->Release();
		pEditorDevice = 0;
	}
}