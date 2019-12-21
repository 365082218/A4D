#pragma once
#include "../A4D.h"
class Component;
class RenderTexture;
class BoundFrustum;
class Transform;
class A4D;
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
	bool orthographic;//���ͶӰ��ʽ
	int depth;
	int CullingMask;//����ͼ��
	float fieldOfView;//The field of view of the camera in degrees.
	float aspect;//��߱�
	D3DVIEWPORT9 viewport;
	D3DVIEWPORT9 normalizedViewport;
	RECT viewportRect;//�ӿ�
	float nearplane;//��������
	float farplane;//Զ������
	int clearFlag;
	//CLEARFLAG_SOLIDCOLOR = 0;��ɫ
	//CLEARFLAG_SKY = 1;��պ�
	//CLEARFLAG_DEPTHONLY = 2;���
	//CLEARFLAG_NONE = 3;������
	D3DCOLOR background;
	int id;
	void _renderCamera(IDirect3DDevice9 * pDevice, RenderState * rs, Scene * pScene);
	void _prepareCameraViewProject(D3DMATRIX * pViewM, D3DMATRIX * pProjM);
	void _prepareCameraToRender();
	RenderTexture * _renderTarget;
	bool useOcclusionCulling;
	BoundFrustum * boundFrustum;//׶����
	void OnEnable(Event * context);
	void OnDisable(Event * context);
	size_t type_id()
	{
		return typeid(Camera).hash_code();
	}

	void SetViewPort(D3DVIEWPORT9 * port);
};

