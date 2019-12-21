#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"
#include "Camera.h"
#include "Layer.h"
#include "RenderState.h"
#include "RenderTexture.h"
#include "BoundFrustum.h"
#include "object.h"

REGISTER_CLASS(Camera);
Camera::Camera()
{
	nearplane = 0.3f;
	farplane = 1000;
	fieldOfView = 60;
	
	orthographic = false;

	viewport.X = 0;
	viewport.Y = 0;
	viewport.Height = A4D::height();
	viewport.Width = A4D::width();
	viewport.MinZ = -1;
	viewport.MaxZ = 1;

	aspect = (float)viewport.Width / viewport.Height;

	normalizedViewport.X = 0;
	normalizedViewport.Y = 0;
	normalizedViewport.Height = 1;
	normalizedViewport.Width = 1;
	normalizedViewport.MinZ = -1;
	normalizedViewport.MaxZ = 1;

	CalculateProjectionMatrix();
	_renderTarget = NULL;
	useOcclusionCulling = false;
}

Camera::~Camera()
{
}

void Camera::OnEnable(Event * context)
{
	if (context->psender->type_id() == typeid(Camera).hash_code())
		gameObject->m_pScene->registerCamera(dynamic_cast<Camera*>(context->psender));
}

void Camera::OnDisable(Event * context)
{
	if (context->psender->type_id() == typeid(Camera).hash_code())
		gameObject->m_pScene->unregisterCamera(this);
}

void Camera::Awake(GameObject * pOwner)
{
	__super::Awake(pOwner);
	
}

void Camera::WorldToViewportPoint(D3DXVECTOR3 * pout, D3DXVECTOR3 * worldPos)
{
	//D3DVIEWPORT9
}

void Camera::CalculateProjectionMatrix()
{
	if (orthographic)
	{
		D3DXMatrixOrthoLH(&projectionMatrix, A4D::width(), A4D::height(), nearplane, farplane);
	}
	else
	{
		D3DXMatrixPerspectiveFovLH(
			&projectionMatrix,
			fieldOfView * D3DX_PI / 180.0f,
			aspect,
			nearplane,
			farplane);
	}
}

void Camera::CalculateViewPort(D3DVIEWPORT9 * normalize, float width, float height)
{
	float x = normalize->X * width;
	float y = normalize->Y * height;
	float wx = x + max(normalize->Width * width, 0);
	float wy = y + max(normalize->Height * height, 0);
	float ceilleftx = ceil(x);
	float ceillefty = ceil(y);
	float floorrightx = floor(wx);
	float floorrighty = floor(wy);
	float pixelleftx = ceilleftx - x >= 0.5 ? floor(x) : ceilleftx;
	float pixellefty = ceillefty - y >= 0.5 ? floor(y) : ceillefty;
	float pixelrightx = wx - floorrightx >= 0.5 ? ceil(wx) : floorrightx;
	float pixelrighty = wy - floorrighty >= 0.5 ? ceil(wy) : floorrighty;
	viewport.X = pixelleftx;
	viewport.Y = pixellefty;
	viewport.Width = pixelrightx - pixelleftx;
	viewport.Height = pixelrighty - pixellefty;
}

void Camera::_prepareCameraToRender()
{
	Layer::_currentCameraCullingMask = this->CullingMask;
}

/*
设置视矩阵和投影矩阵
*/
void Camera::_prepareCameraViewProject(D3DMATRIX * pViewM, D3DMATRIX * pProjM)
{

}

//每个相机都要把所在场景的所有物体全部绘制一遍，如果在该相机的可视层和视锥体内
void Camera::_renderCamera(IDirect3DDevice9 * pDevice, RenderState * rs, Scene * pScene)
{
	//PSSM阴影贴图(scene.parallelSplitShadowMaps[0]) && (scene._renderShadowMap(gl, state, this));
	//PSSM(Parallel Split Shadow Map)平行分割阴影图
	rs->camera = this;
	this->_prepareCameraToRender();

	D3DMATRIX * projectMat = NULL;
	D3DXVECTOR3 vLookat = this->gameObject->transform->position + this->gameObject->transform->forward;
	D3DXMatrixLookAtLH((D3DXMATRIX*)&rs->_viewMatrix, (D3DXVECTOR3*)(&this->gameObject->transform->position), &vLookat, (D3DXVECTOR3*)(&this->gameObject->transform->up));
	RenderTexture * renderTar = this->_renderTarget;
	if (renderTar) {
		//先不考虑渲染到目标
		renderTar->start();
		//Matrix4x4.multiply(BaseCamera._invertYScaleMatrix, this->_projectionMatrix, BaseCamera._invertYProjectionMatrix);
		//Matrix4x4.multiply(BaseCamera._invertYScaleMatrix, this->_projectionViewMatrix, BaseCamera._invertYProjectionViewMatrix);
		//projectMat = state._projectionMatrix = BaseCamera._invertYProjectionMatrix;
		//state._projectionViewMatrix = BaseCamera._invertYProjectionViewMatrix;
	}
	else {
		projectMat = rs->_projectionMatrix = &this->projectionMatrix;
	}
	this->_prepareCameraViewProject(&rs->_viewMatrix, projectMat);
	rs->_viewport = &this->viewport;
	pScene->_preRenderScene(pDevice, rs, this->boundFrustum);
	pScene->_clear(pDevice, rs);
	pScene->_renderScene(pDevice, rs);
	pScene->_postRenderUpdateComponents(rs);
	if (renderTar)
		renderTar->end();
}

void Camera::SetViewPort(D3DVIEWPORT9 * port)
{
	float width = A4D::width();
	float height = A4D::height();
	normalizedViewport.X = port->X / width;
	normalizedViewport.Y = port->Y / height;
	normalizedViewport.Width = port->Width / width;
	normalizedViewport.Height = port->Height / height;
	CalculateViewPort(&normalizedViewport, width, height);
	CalculateProjectionMatrix();
}