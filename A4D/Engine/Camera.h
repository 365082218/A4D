#pragma once
class WGraphics;
class RenderState;
class RenderTexture;
class BoundFrustum;
#include "Component.h"
class Camera :public Component
{
public:
	Camera();
	~Camera();
	void Awake(GameObject * pGameObject);
	void CalculateProjectionMatrix();
	void CalculateViewPort(D3DVIEWPORT9 *normalize, float width, float height);
	D3DXMATRIX projectionMatrix;
	void WorldToViewportPoint(D3DXVECTOR3 * pout, D3DXVECTOR3 * worldPos);
	bool orthographic;//相机投影方式
	int depth;
	int CullingMask;//可视图层
	float fieldOfView;//The field of view of the camera in degrees.
	float aspect;//宽高比
	D3DVIEWPORT9 viewport;
	D3DVIEWPORT9 normalizedViewport;
	RECT viewportRect;//视口
	float nearplane;//近剪裁面
	float farplane;//远剪裁面
	int clearFlag;
	//CLEARFLAG_SOLIDCOLOR = 0;纯色
	//CLEARFLAG_SKY = 1;天空盒
	//CLEARFLAG_DEPTHONLY = 2;深度
	//CLEARFLAG_NONE = 3;不擦除
	D3DCOLOR background;
	int id;
	void _renderCamera(IDirect3DDevice9 * pDevice, RenderState * rs, WGraphics * pGraphics);
	void _prepareCameraViewProject(D3DMATRIX * pViewM, D3DMATRIX * pProjM);
	void _prepareCameraToRender();
	RenderTexture * _renderTarget;
	bool useOcclusionCulling;
	BoundFrustum * boundFrustum;//锥截体
	void OnEnable(AEvent * context);
	void OnDisable(AEvent * context);
	size_t type_id()
	{
		return typeid(Camera).hash_code();
	}

	void SetViewPort(D3DVIEWPORT9 * port);
};

